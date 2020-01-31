#include "Ground.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"

extern Game * game;

Ground::Ground(QGraphicsItem *parent): Obstacle(parent){

    setPixmap(QPixmap(":/textures/resources/textures/concrete.jpg"));
}


