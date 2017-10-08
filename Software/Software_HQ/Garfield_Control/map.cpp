#include "map.h"
#include "ui_map.h"

#include <QProcess>
#include <QDebug>
#include <QPoint>
#include <QMouseEvent>

map::map(QMainWindow *parent) : QWidget(parent),
    map_ui(new Ui::map)
{

    map_ui->setupUi(this);
    map_ui->label_map->setPixmap(QPixmap("/home/lex/Dokumente/BreezySLAM-master/examples/exp2.pgm"));
    map_ui->label_alf->setPixmap(QPixmap("/home/lex/Downloads/auto.png"));
    map_ui->label_destination->setPixmap(QPixmap("/home/lex/Downloads/fahne3.png"));

    connect(map_ui->label_map,SIGNAL(clickedOnMap(QPoint)),this,SLOT(setFlag(QPoint)));
    setMouseTracking(true);


    void setFlag(QPoint pos);
}

void map::open(){
    this->show();
}

void map::mouseMoveEvent(QMouseEvent *ev) {
        QTransform t;
        t.scale(1, -1);
        t.translate(0, -height()+1);
        QPoint pos = ev->pos() * t;
    }


void map::setFlag(QPoint pos){
    map_ui->textEdit_3->setText(QString("%1").arg(pos.x()));
    map_ui->textEdit_4->setText(QString("%1").arg(pos.y()));

    map_ui->label_destination->setGeometry(pos.x()-40,520-pos.y(),map_ui->label_destination->geometry().width(),map_ui->label_destination->geometry().height());
    map_ui->label_destination->show();
}









