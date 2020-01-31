#include "Client.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"

extern Game * game;
Client::Client(QGraphicsItem *parent): Person(parent){
    //set random x and y position
    int random_x = rand() % (game->win_w - 3*PLAYER_WIDTH);
    int random_y = rand() % (game->ceiling - PLAYER_LENGTH);

    setPos(random_x,random_y);

    setPixmap(QPixmap(":/textures/resources/textures/client.png"));

    // make/connect a timer to move() the enemy every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(50);
}


