#ifndef BOMB_H
#define BOMB_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Bomb: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bomb(QGraphicsItem * parent=0);
public slots:
};

#endif // BOMB_H
