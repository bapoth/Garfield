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

    setMouseTracking(true);
}

void map::open(){
    this->show();
}

void map::mouseMoveEvent(QMouseEvent *ev) {
        // vvv That's where the magic happens
        QTransform t;
        t.scale(1, -1);
        t.translate(0, -height()+1);
        QPoint pos = ev->pos() * t;
        // ^^^
        //setText(QString("%1, %2").arg(pos.x()).arg(pos.y()));
        map_ui->textEdit_3->setText(QString("%1").arg(pos.x()));
        map_ui->textEdit_4->setText(QString("%1").arg(pos.y()));
    }

void map::setPosition(QPoint pos){
    map_ui->textEdit_3->setText(QString("%1").arg(pos.x()));
    map_ui->textEdit_4->setText(QString("%1").arg(pos.y()));
}





