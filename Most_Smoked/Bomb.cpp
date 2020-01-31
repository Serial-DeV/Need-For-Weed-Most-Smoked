#include "Bomb.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"

extern Game * game;

Bomb::Bomb(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    //set random x and y position
    int random_x = rand() % game->win_w;
    //int random_y = rand() % (floor);
    int random_y = game->floor - 36; // Elle est forcément au sol
    setPos(random_x,random_y);

    setPixmap(QPixmap(":/textures/resources/textures/bomb.png"));
}


