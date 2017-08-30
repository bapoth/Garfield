#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QMainWindow>
#include <QPoint>

namespace Ui {
class map;
}

class map : public QWidget
{
    Q_OBJECT
public:
    explicit map(QMainWindow *parent = 0);
    Ui::map *map_ui;
    void open();
    void mouseMoveEvent(QMouseEvent *ev);
    void setPosition(QPoint);
signals:

public slots:

};

#endif // MAP_H
