#include "Person.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Game.h"
#include <QtDebug>

extern Game * game;

Person::Person(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    saveX = x();
    saveY = y();
    gForce = 4;

    QTimer * timerGravity = new QTimer(this);
    QObject::connect(timerGravity,SIGNAL(timeout()),this,SLOT(gravity()));
    timerGravity->start(10);
}


void Person::gravity()
{
    saveX = x();
    saveY = y();
    if (checkObstacle())
    {
        setPos(saveX, saveY+1);
        gForce = 0;
    }
    else if (checkGround() && gForce < 0) setPos(saveX,saveY+gForce);
    else if(!(checkGround())) setPos(saveX,saveY+gForce);
    if(gForce < 4) gForce += 0.2;
    if(gForce > 4) gForce = 4;
}

bool Person::checkObstacle()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){

        if (typeid(*(colliding_items[i])) == typeid(Obstacle)){
            setPos(saveX,saveY);
            return true;
        }
    }
    return false;
}

bool Person::checkGround()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){

        if (typeid(*(colliding_items[i])) == typeid(Ground)){
            setPos(saveX,colliding_items[i]->y()-29.99999999999);
            return true;
        }
    }
    return false;
}


