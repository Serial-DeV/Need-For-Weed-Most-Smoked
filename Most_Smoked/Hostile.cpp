#include "Hostile.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"

#include "QDebug"

extern Game * game;

Hostile::Hostile(QGraphicsItem *parent): Enemy(parent){
 setPixmap(QPixmap(":/textures/resources/textures/hostile2.png"));

 QTimer * timerMove = new QTimer(this);
 QObject::connect(timerMove,SIGNAL(timeout()),this,SLOT(move()));
 timerMove->start(10);

}

void Hostile::move()
{
    if(Enemy::goRight)
    {
        setPixmap(QPixmap(":/textures/resources/textures/hostile2.png"));
    }
    else if(Enemy::goLeft)
    {
        setPixmap(QPixmap(":/textures/resources/textures/hostile3.png"));
    }
}
