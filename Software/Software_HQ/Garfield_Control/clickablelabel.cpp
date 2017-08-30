#include "clickablelabel.h"
#include <QPoint>
#include <QMouseEvent>
#include <stdio.h>
ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
    setMouseTracking(true);
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked();

    QTransform t;
    t.scale(1, -1);
    t.translate(0, -height()+1);
    QPoint pos = event->pos() * t;
    //map::setPosition(pos);

}
