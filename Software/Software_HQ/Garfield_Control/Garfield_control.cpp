/*!
 * @file
 * */
#include "QSettings"

#include "alf_data.hpp"
#include "alf_data_info.hpp"

#include "joystick.h"
#include "Garfield_control.h"
#include "Settings.h"
#include "ui_Garfield_control.h"
#include "ui_Settings.h"

#include <QtConcurrent>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <qpainter.h>

//P:
//#include <mutex>
#include <condition_variable>

#define ANGLE_MAX_VAL 90
#define ANGLE_MIN_VAL -90
#define SPEED_MAX_VAL 255
#define SPEED_MIN_VAL 0
#define ACC_MAX_VAL 2.0
#define ACC_MIN_VAL -2.0

#define POLLING_GAMEPAD_INTERVAL_MS 1

#define ACC_MAP_UPDATE_MS 20

#define SEND_REC_INTERVAL_MS 20
#define DEBUG 1

//P:
/// global variables for switching map between HQ and ARM
std::condition_variable Run_getMapThread;
bool notify_getMapThread = false;
bool invokedCopyingMapFinished = false;

Garfield_control::Garfield_control(QMainWindow *parent) :  QMainWindow(parent),
    ui(new Ui::Garfield_control)
    {
    ui->setupUi(this);
    //ui->label->setPixmap(QPixmap("/home/lex/Dokumente/BreezySLAM-master/examples/exp2.pgm"));
    //ui->label_2->setPixmap(QPixmap("/home/lex/Downloads/auto.png"));
    //Set initial values
    _speed = 0;
    _direction = 0;
    _angle = 0;
    _light = false;
    x_position = 390;
    y_position = 390;

    //Load Settings
    m_sSettingsFile = QApplication::applicationDirPath() + "/Garfield.conf";
    loadSettings();

    //Gamepad
    connect_gamepad();


    connect(ui->pushButton_up, SIGNAL(pressed()), this, SLOT(command_forward()));
    connect(ui->pushButton_up, SIGNAL(released()), this, SLOT(command_forback_rel()));
    connect(ui->pushButton_down, SIGNAL(pressed()), this, SLOT(command_back()));
    connect(ui->pushButton_down, SIGNAL(released()), this, SLOT(command_forback_rel()));
    connect(ui->pushButton_left, SIGNAL(pressed()), this, SLOT(command_left()));
    connect(ui->pushButton_left, SIGNAL(released()), this, SLOT(command_leftright_rel()));
    connect(ui->pushButton_right, SIGNAL(pressed()), this, SLOT(command_right()));
    connect(ui->pushButton_right, SIGNAL(released()), this, SLOT(command_leftright_rel()));
    connect(ui->checkBox_light, SIGNAL(stateChanged(int)), this, SLOT(command_toggleLights(int)));

    //UI Default values
    ui->angle_lineEdit->setText("0");
    ui->speed_lineEdit->setText("0");
    ui->Gyro_X_lineEdit->setText("0");
    ui->Gyro_Y_lineEdit->setText("0");
    ui->Gyro_Z_lineEdit->setText("0");
    ui->temperatur_lineEdit->setText("0.0");

    //Debug Settings
    ui->DebugSlider_Dir->setVisible(false);
    ui->DebugSlider_speed->setVisible(false);
    connect(ui->actionDebug, SIGNAL(triggered(bool)), this, SLOT(debug_settings(bool)));
    connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(open_settings()));
    connect(ui->actionMap, SIGNAL(triggered()), this, SLOT(open_map()));


    //Connection Button & Label
    _connected = false;
    connect(ui->connect_pushButton, SIGNAL(clicked(bool)), this, SLOT(open_close_connection()));
    ui->connstate_label->hide();

    //Acceleration
    ui->AccGrid_label->setPixmap(QPixmap(QApplication::applicationDirPath() + "/acceleration_grid.png"));
    ui->GridPoint_label->setPixmap(QPixmap(QApplication::applicationDirPath() + "/acceleration_point.png"));

    GridPointPos = ui->GridPoint_label->pos();

    UpdateAccTimer = new QTimer(this);
    connect(UpdateAccTimer, SIGNAL(timeout()), this, SLOT(update_acceleration()));
    UpdateAccTimer->start(ACC_MAP_UPDATE_MS);

    _acceleration = 0;
    _lateral_acceleration = 0;
}

Garfield_control::~Garfield_control()
{
    GamepadTimer->stop();
    UpdateAccTimer->stop();
    open_close_connection();
    delete ui;

    qDebug()<<"Quit Program";
}

bool Garfield_control::connect_gamepad() {

    std::string input ("/dev/input/");
    input+=_Dev.toUtf8().constData();
    _joystick = new Joystick(input);

    if(_joystick->isFound()) {
        GamepadTimer = new QTimer(this);
        connect(GamepadTimer, SIGNAL(timeout()), this, SLOT(poll_gamepad()));
        GamepadTimer->start(POLLING_GAMEPAD_INTERVAL_MS);

        return true;
    }
    else {
        ui->statusBar->showMessage("No gamepad connected, check settings whether gamepad is detected", 5000);
        return false;
    }
}

void Garfield_control::poll_gamepad() {
    static JoystickEvent event;
    if(_joystick->isFound()) { //Joystick is present
        if (_joystick->sample(&event))
        {
            if (event.isButton())
            {
                if(event.number == GAMEPAD_BUTTON_TRIANGLE && event.value == GAMEPAD_BUTTON_DOWN) {
                    ui->checkBox_light->toggle();
                }
            }
            else if (event.isAxis())
            {

                //Backwards
                if(event.number == GAMEPAD_AXIS_L2) {
                    command_setBackSpeed(norm_value(GAMEPAD_AXIS_UP, GAMEPAD_AXIS_DOWN, SPEED_MIN_VAL, SPEED_MAX_VAL, static_cast<int>(event.value)));
                }
                //Forwards
                else if(event.number == GAMEPAD_AXIS_R2) {
                    command_setForwardSpeed(norm_value(GAMEPAD_AXIS_UP, GAMEPAD_AXIS_DOWN, SPEED_MIN_VAL, SPEED_MAX_VAL, static_cast<int>(event.value)));
                }
                if(event.number == GAMEPAD_AXIS_ANALOG_LEFT_LR) {
                    command_setDirection(norm_value(GAMEPAD_AXIS_UP, GAMEPAD_AXIS_DOWN, ANGLE_MIN_VAL, ANGLE_MAX_VAL, static_cast<int>(event.value)));
                }
            }
        }
    }
    else { //No joystick anymore set speed and direction to 0 and stop timer
        command_setForwardSpeed(0.0);
        command_setDirection(0.0);
        GamepadTimer->stop();
        ui->statusBar->showMessage("Gamepad lost connection, will stop vehicle!", 5000);
    }
}

void Garfield_control::update_acceleration() {

    if(_lateral_acceleration > ACC_MAX_VAL) {
        _lateral_acceleration = ACC_MAX_VAL;
    }
    else if(_lateral_acceleration < ACC_MIN_VAL) {
        _lateral_acceleration = ACC_MIN_VAL;
    }

    if(_acceleration > ACC_MAX_VAL) {
        _acceleration = ACC_MAX_VAL;
    }
    else if(_acceleration < ACC_MIN_VAL) {
        _acceleration = ACC_MIN_VAL;
    }

    //qDebug()<<static_cast<int>(norm_value(ACC_MIN_VAL, ACC_MAX_VAL, -60.0, 60.0, _lateral_acceleration));

    //Take origin position, subtract current x_shift and add new x_shift
    int x_pos = ui->GridPoint_label->pos().rx() - (ui->GridPoint_label->pos().rx() - GridPointPos.rx()) + static_cast<int>(norm_value(ACC_MIN_VAL, ACC_MAX_VAL, -60.0, 60.0, _lateral_acceleration));

    //Take origin position, subtract old x_shift and add new x_shift (negative value shifts up)
    int y_pos = ui->GridPoint_label->pos().ry() - (ui->GridPoint_label->pos().ry() - GridPointPos.ry()) - static_cast<int>(norm_value(ACC_MIN_VAL, ACC_MAX_VAL, -60.0, 60.0, _acceleration));

    ui->GridPoint_label->move(x_pos, y_pos);
}

void Garfield_control::keyPressEvent(QKeyEvent* e) {

    if(e->key() == Qt::Key_L) {
        ui->checkBox_light->toggle(); //When state is toggled, SLOT funtcion get called automatically, so nothing more to be done
    }
    if(e->key() == Qt::Key_W) {
        ui->pushButton_up->setDown(true);
        command_forward();
        y_position--;
    }
    if(e->key() == Qt::Key_S) {
        ui->pushButton_down->setDown(true);
        command_back();
        y_position++;
    }
    if(e->key() == Qt::Key_D) {
        ui->pushButton_right->setDown(true);
        command_right();
        x_position++;
    }
    if(e->key() == Qt::Key_A) {
        ui->pushButton_left->setDown(true);
        command_left();
        x_position--;
    }
    //ui->label_2->setGeometry(x_position,y_position,ui->label_2->geometry().width(),ui->label_2->geometry().height());
    //ui->label_2->show();

    QMainWindow::keyPressEvent(e);
}

void Garfield_control::keyReleaseEvent(QKeyEvent* e) {

    if(e->key() == Qt::Key_W) {
        ui->pushButton_up->setDown(false);
        command_forback_rel();
    }
    if(e->key() == Qt::Key_S) {
        ui->pushButton_down->setDown(false);
        command_forback_rel();
    }
    if(e->key() == Qt::Key_D) {
        ui->pushButton_right->setDown(false);
        command_leftright_rel();
    }
    if(e->key() == Qt::Key_A) {
        ui->pushButton_left->setDown(false);
        command_leftright_rel();
    }

    QMainWindow::keyReleaseEvent(e);
}

void Garfield_control::command_forward() {
    ui->DebugSlider_speed->setValue(ui->DebugSlider_speed->maximum());
    _speed = SPEED_MAX_VAL;
    _direction = 0;
}

void Garfield_control::command_back() {
    ui->DebugSlider_speed->setValue(ui->DebugSlider_speed->minimum());
    _speed = SPEED_MAX_VAL;
    _direction = 1;
}

void Garfield_control::command_forback_rel() {
    ui->DebugSlider_speed->setValue(ui->DebugSlider_speed->maximum()-((ui->DebugSlider_speed->maximum()-ui->DebugSlider_speed->minimum())/2));
    _speed = SPEED_MIN_VAL;
    _direction = 0; //Set on key release initial direction to 0 (forward)
}

void Garfield_control::command_left() {
    ui->DebugSlider_Dir->setValue(ui->DebugSlider_Dir->minimum());
    ui->angle_lineEdit->setText(QString::number(ANGLE_MIN_VAL));
    _angle = ANGLE_MIN_VAL;
}

void Garfield_control::command_right() {
    ui->DebugSlider_Dir->setValue(ui->DebugSlider_Dir->maximum());
    ui->angle_lineEdit->setText(QString::number(ANGLE_MAX_VAL));
    _angle = ANGLE_MAX_VAL;
}

void Garfield_control::command_leftright_rel() {
    ui->DebugSlider_Dir->setValue(ui->DebugSlider_Dir->maximum()-((ui->DebugSlider_Dir->maximum()-ui->DebugSlider_Dir->minimum())/2));
    ui->angle_lineEdit->setText(QString::number((ANGLE_MAX_VAL-std::abs(ANGLE_MIN_VAL))/2));
    _angle = (ANGLE_MAX_VAL-std::abs(ANGLE_MIN_VAL))/2;
}

void Garfield_control::command_setForwardSpeed(double value) {
    qDebug() << "Forward: "<<value;
    ui->DebugSlider_speed->setValue(value);
    _direction = 0;
    _speed = (int)(value);
}

void Garfield_control::command_setBackSpeed(double value) {
    qDebug() << "Back: "<<value;
    ui->DebugSlider_speed->setValue(value*-1);
    _direction = 1;
    _speed = (int)(value);
}

void Garfield_control::command_setDirection(double value) {
    qDebug() << "Direction: "<<value;
    ui->angle_lineEdit->setText(QString::number((int)value));
    _angle = (int)(value);
    ui->DebugSlider_Dir->setValue(_angle+90); //weird behavior of Slider (variable has correct value, but slider is in wrong position)
}

void Garfield_control::command_toggleLights(int state) {

    if(state == 2) { //checked
        qDebug() << "On";
        _light = true;
    }
    else if(state == 0) { //unchecked
        qDebug() << "Off";
        _light = false;
    }
}

void Garfield_control::debug_settings(bool state) {
    if (state == true) {
        debug = true;
        ui->DebugSlider_Dir->setVisible(true);
        ui->DebugSlider_speed->setVisible(true);
    }
    else {
        debug = false;
        ui->DebugSlider_Dir->setVisible(false);
        ui->DebugSlider_speed->setVisible(false);
    }
}

void Garfield_control::open_settings() {
    settings = new Settings(this, _IP, _Port, _Dev);
    connect(settings, SIGNAL(accepted()), this, SLOT(closed_settings()));

    settings->open();
}

void Garfield_control::closed_settings() {
    _IP = settings->settings_ui->ip_lineEdit->text();
    _Port = settings->settings_ui->port_lineEdit->text();
    _Dev = settings->settings_ui->contr_comboBox->currentText();
    delete settings;
    saveSettings();

    if(_joystick->isFound()) {
        delete _joystick;
    }
    connect_gamepad();
}

void Garfield_control::loadSettings()
{
 QSettings setting(m_sSettingsFile, QSettings::NativeFormat);

 _IP = setting.value("ip", "").toString();
 _Port = setting.value("port", "").toString();
 _Dev = setting.value("dev", "").toString();
}

void Garfield_control::saveSettings()
{
 QSettings settings(m_sSettingsFile, QSettings::NativeFormat);

 settings.setValue("ip", _IP);
 settings.setValue("port", _Port);
 settings.setValue("dev", _Dev);
}

void Garfield_control::open_map() {
    mymap = new map();
    connect(this,SIGNAL(displayAlfPosition(int,int,double)),mymap,SLOT(setAlfPosition(int,int,double)));
    //connect(mymap, SIGNAL(accepted()), this, SLOT(closed_map()));
    //mymap->show();
    mymap->open();
}
void Garfield_control::closed_map() {

}

void Garfield_control::getIP(QString *IP) {
    *IP = _IP;
}

void Garfield_control::getPort(int *Port) {
    *Port = _Port.toInt();
}

void Garfield_control::setSpeed(int speed) {
    _speed=speed;
}

void Garfield_control::setAngle(int angle) {
    _angle = angle;
}

void Garfield_control::setLight(bool light) {
    _light = light;
}

void Garfield_control::getSpeed(int &speed) {
    speed = _speed;
}

void Garfield_control::getAngle(int &angle) {
    angle = _angle;
}

void Garfield_control::getLight(bool &light) {
    light = _light;
}

void Garfield_control::open_close_connection() {
    static QFuture<void> f1;
    static QFuture<void> f2;

    static QFuture<void> f3;


    if(_connected==false) {
        bool ret = ClientComm.Init(_IP.toUtf8().constData(), _Port.toInt());

        if(ret) {
            _connected = true;
            _disconnect = false;
            ui->connstate_label->setText("connected");
            ui->connstate_label->setStyleSheet("QLabel {color : green;}");
            ui->connect_pushButton->setText("disconnect");

            f1 = QtConcurrent::run(this, &Garfield_control::sendThread);

            f2 = QtConcurrent::run(this, &Garfield_control::recThread);
            f3 = QtConcurrent::run(this, &Garfield_control::getMapThread);//P:
            //f2 = QtConcurrent::run(this, &Garfield_control::recThread);
	//            f3 = QtConcurrent::run(this, &Garfield_control::mapThread);




        }
        else {
            ui->connstate_label->setText("not connected");
            ui->connstate_label->setStyleSheet("QLabel {color : red;}");
            ui->connect_pushButton->setText("connect");
            _connected =  false;
        }
        ui->connstate_label->show();
    }
    else {
        _connected = false;
        _disconnect = true;

        f1.cancel();
        f2.cancel();
        f3.cancel();//P:

        ClientComm.EndCommunication();
        ui->connstate_label->hide();
        ui->connect_pushButton->setText("connect");
    }

}

void Garfield_control::sendThread() {

    while(!_disconnect) {

        //P:
        // decide if invoked request by ARM was fullfilled
        if(invokedCopyingMapFinished)
        {
            printf("Test: Send Reply to ARM after Copyying map\n");
            global_drive_command.finishedCopyMapFile = true;
            invokedCopyingMapFinished = false;
        } else {
            global_drive_command.finishedCopyMapFile = false;
        }

        global_drive_command.speed = _speed;
        global_drive_command.direction = _direction;
        global_drive_command.angle = _angle;
        global_drive_command.light = _light;
        //if(DEBUG) printf("\n sendthread.... \n");
        ClientComm.Write(global_drive_command);

        QThread::msleep(SEND_REC_INTERVAL_MS);
    }
    return;
}

void Garfield_control::recThread() {
    Alf_Urg_Measurements_Buffer readBuffer(10);
    alf_mess_types msgType;

    printf("\n recThread started");
    while(!_disconnect) {

        if (DEBUG) printf("readThread\n");
        alf_error myError = ClientComm.Read(readBuffer, msgType);
        if (DEBUG) printf("error :%s      ",std::to_string(myError));
        if(msgType == ALF_END_ID) {
            qDebug()<<"End";
            _disconnect = true;
        }

        ui->speed_lineEdit->setText(QString::number(global_drive_info.speed));
        _acceleration = global_drive_info.acceleration;
        _lateral_acceleration = global_drive_info.lateral_acceleration;


        ui->Gyro_X_lineEdit->setText(QString::number(global_drive_info.Gyroscope_X));
        ui->Gyro_Y_lineEdit->setText(QString::number(global_drive_info.Gyroscope_Y));
        ui->Gyro_Z_lineEdit->setText(QString::number(global_drive_info.Gyroscope_Z));

        ui->temperatur_lineEdit->setText(QString::number(global_drive_info.temperature));

        if(mymap != NULL){
            emit displayAlfPosition(global_drive_info.x_position,global_drive_info.y_position,global_drive_info.theta_position);
        }

        if(msgType == ALF_POSITION_ID){
            printf("got position\n");
            x_position = global_alf_position.x_position;
            y_position = global_alf_position.y_position;
        }

        //P:
        // Check, if ARM send a request to invoke the copying of map-pgm-file on the vehicle
        // If Yes, invoke the copying
        printf("Test: invokeCopyMapFilee = %d\n", global_drive_info.invokeCopyMapFile);
        if(global_drive_info.invokeCopyMapFile)
        {
            printf("Test: Request is received from ARM\n");
            notify_getMapThread = true;
            Run_getMapThread.notify_one();
            global_drive_info.invokeCopyMapFile = false;
        }

        QThread::msleep(SEND_REC_INTERVAL_MS);
    }
    open_close_connection();
    return;
}

//P:
void Garfield_control::getMapThread() {

    std::mutex mux;
    std::unique_lock<std::mutex> lock(mux);

    while(!_disconnect) {

        // thread sleep until notified by request of ARM
        while(not notify_getMapThread){
            Run_getMapThread.wait(lock);
        }
        printf("Test: Copy the map-pgm-file from ARM to HQ\n");
        notify_getMapThread = false;

        system("sudo sshpass -p temppwd scp -o StrictHostKeyChecking=no ubuntu@192.168.100.149:/home/ubuntu/bin/savingSlamMap.pgm /home/lex/Dokumente/testSavingSSH.pgm");
        if(mymap != NULL)
            mymap->setMapImage();
        invokedCopyingMapFinished = true;

        // QThread::msleep(3000);
    }
    open_close_connection();
    return;
}


void Garfield_control::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 30));
    QPen linepen(Qt::red);
    linepen.setCapStyle(Qt::RoundCap);
    linepen.setWidth(10);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(linepen);


    painter.drawPoint(x_position,y_position);

    //painter.drawText(rect(), Qt::AlignCenter, "Qt");
}

void Garfield_control::on_pushButton_clicked()
{
    //ui->label->setPixmap(QPixmap("/home/lex/Dokumente/BreezySLAM-master/examples/exp4.pgm"));
   // ui->label->show();
}

