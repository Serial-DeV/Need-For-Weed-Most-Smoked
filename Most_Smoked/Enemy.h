#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Person.h"

class Enemy: public Person{
    Q_OBJECT
public:
    Enemy(QGraphicsItem * parent=0);
public slots:
protected:
    bool updateDir;
    bool goLeft;
    bool goRight;
private slots:
    void move();
    void updateMove();
private:

};

#endif // ENEMY_H
