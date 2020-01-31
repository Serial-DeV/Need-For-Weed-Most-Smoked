#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Obstacle: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Obstacle(QGraphicsItem * parent=0);
public slots:
};

#endif // OBSTACLE_H
