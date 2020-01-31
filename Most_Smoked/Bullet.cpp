#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include "Client.h"
#include "Game.h"
#include "Police.h"
#include "Hostile.h"


#define BULLET_WIDTH 1
#define BULLET_LENGTH 5
#define BULLET_SPEED 2

#include <QDebug>

extern Game * game; // there is an external global object called game

Bullet::Bullet(QGraphicsItem *parent, int n): QObject(), QGraphicsRectItem(parent){
    // drew the bullet (a rectangle)
    direction = n;
    switch (direction) {
        case 6: // Right
            setRect(PLAYER_WIDTH,(PLAYER_LENGTH/2)-(BULLET_WIDTH/2),BULLET_LENGTH,BULLET_WIDTH);
        break;
        case 4: // Left
            setRect(0-BULLET_LENGTH,(PLAYER_LENGTH/2)-(BULLET_WIDTH/2),BULLET_LENGTH,BULLET_WIDTH);
        break;
    }



    // make/connect a timer to move() the bullet every so often
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(3);


    nanisound = new QMediaPlayer();
    ughsound = new QMediaPlayer();
    nanisound->setMedia(QUrl("qrc:/sounds/resources/sounds/nani.ogg"));
    ughsound->setMedia(QUrl("qrc:/sounds/resources/sounds/ugh.ogg"));
}

void Bullet::move(){
    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    // if one of the colliding items is an Enemy, destroy both the bullet and the enemy
    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Police) || typeid(*(colliding_items[i])) == typeid(Hostile))
        {
            // play ughsound
            if (ughsound->state() == QMediaPlayer::PlayingState)
            {
                ughsound->setPosition(0);
            }
            else ughsound->play();

            // increase the score
            game->player->get_score()->increase();

            int val;
            if (typeid(*(colliding_items[i])) == typeid(Police)) val = 20;
            else if (typeid(*(colliding_items[i])) == typeid(Hostile)) val = 6;
            game->player->get_wanted()->increase(val);

            // remove them from the scene (still on the heap)
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // delete them from the heap to save memory
            delete this;
            game->nbEnemy--;
            qDebug()<<"Il y a "<< game->nbEnemy <<"ennemis\n";
            // return (all code below refers to a non existint bullet)
            game->player->checklevel();

            return;
        }
        // if one of the colliding items is an Client, destroy both the bullet and the client
        if (typeid(*(colliding_items[i])) == typeid(Client))
        {
            // play nanisound
            if (nanisound->state() == QMediaPlayer::PlayingState)
            {
                nanisound->setPosition(0);
            }
            else nanisound->play();

             //qDebug() << "Touché client";
            // remove them from the scene (still on the heap)
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);

            // Save client position
            int x = colliding_items[i]->x();
            int y = colliding_items[i]->y();

            // delete them from the heap to save memory
            delete this;
            game->nbClient--;

            // Client become an Enemy
            game->player->unconditional_spawn(x, y);

            // return (all code below refers to a non existint bullet)
            return;
        }



        if (typeid(*(colliding_items[i])) == typeid(Obstacle)){

            // remove them from the scene
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // if there was no collision with an Enemy, move the bullet forward

    if (direction == 6) // Right
    {
    setPos(x()+BULLET_SPEED,y());
    }

    else if (direction == 4) // Left
    {
    setPos(x()-BULLET_SPEED,y());
    }


    // if the bullet is off the screen, destroy it
    if (pos().y() + rect().height() < 0 || pos().y() > game->win_h || pos().x() + rect().height() < 0 ||  pos().x() > game->win_w ){
        scene()->removeItem(this);
        delete this;
    }
}
