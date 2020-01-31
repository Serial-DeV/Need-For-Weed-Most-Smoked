#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "Game.h"
#include <QtDebug>

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): Person(parent){
    //set random x and y position
    int random_x = rand() % (game->win_w - 3*PLAYER_WIDTH);
    int random_y = rand() % (game->ceiling - PLAYER_LENGTH);
    setPos(random_x,random_y);

    saveX = x();
    saveY = y();

    QTimer * timerMove = new QTimer(this);
    QObject::connect(timerMove,SIGNAL(timeout()),this,SLOT(move()));
    timerMove->start(10);

    QTimer * timerMoveReaction = new QTimer(this);
    QObject::connect(timerMoveReaction,SIGNAL(timeout()),this,SLOT(updateMove()));
    timerMoveReaction->start(500);

    updateDir = false;
    goLeft = false;
    goRight = false;
}

   void Enemy::updateMove()
   {
       updateDir = true;
   }

   void Enemy::move()
   {
       if(game->player->Person::x() > Person::x() && checkGround() && (updateDir || goRight))
       {
           setPos(Person::x() + 1 ,Person::y());
           updateDir = false;
           goRight = true;
           goLeft = false;
       }
       else if(game->player->Person::x() < Person::x() && checkGround() && (updateDir || goLeft))
       {
           setPos(Person::x() - 1 ,Person::y());
           updateDir = false;
           goLeft = true;
           goRight = false;
       }
       else
       {
           goLeft = false;
           goRight = false;
       }
   }
