#include "BulletCounter.h"
#include <QFont>
#include "Game.h"

extern Game * game;

BulletCounter::BulletCounter(QGraphicsItem *parent): QGraphicsTextItem(parent){


    init_bullets();
    // draw the text
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
    setZValue(1); // on top
}

 int BulletCounter::get_bullets()
 {
     return bullet_amount;
 }

 void BulletCounter::init_bullets()
 {
    bullet_amount = 100;
    setPlainText(QString("Bullets: ") + QString::number(bullet_amount));
 }

 void BulletCounter::increase_bullets(int n)
 {
    bullet_amount+=n;
    setPlainText(QString("Bullets: ") + QString::number(bullet_amount));
 }


 void BulletCounter::decrease_bullets()
 {
    bullet_amount--;
    setPlainText(QString("Bullets: ") + QString::number(bullet_amount));
 }

