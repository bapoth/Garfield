#include "clickablelabel.h"
#include <QPoint>
#include <QMouseEvent>
#include <stdio.h>
#include "map.h"
ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags)
    : QLabel(parent) {
    setMouseTracking(true);
}

ClickableLabel::~ClickableLabel() {


    void clickedOnMap(QPoint pos);
}

void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    //emit clicked();

    QTransform t;
    t.scale(1, -1);
    t.translate(0, -height()+1);
    QPoint pos = event->pos() * t;
    //map::setPosition(pos);
  // parentWidget()->move(pos);
    emit clickedOnMap(pos);

}
