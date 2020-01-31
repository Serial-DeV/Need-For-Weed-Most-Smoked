#include "Obstacle.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"

extern Game * game;

Obstacle::Obstacle(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    setPos(0,0);
    setPixmap(QPixmap(":/textures/resources/textures/brickWall.jpg"));
}


