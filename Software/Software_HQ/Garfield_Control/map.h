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
    void move(const QPoint pos);
signals:

public slots:
    void setFlag(QPoint pos);

};

#endif // MAP_H
