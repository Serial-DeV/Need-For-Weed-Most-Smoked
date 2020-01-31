#include "Wanted.h"
#include <QFont>
#include <QTimer>
#include <QtDebug>

Wanted::Wanted(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // initialize the wanted level to 0
    wanted = 0.0;
     setPixmap(QPixmap(":/textures/resources/textures/0-star.png"));

    setZValue(1); // on top
    b = false;

    // make/connect a timer to move() the enemy every so often
    QTimer * timerStars = new QTimer(this);
    connect(timerStars,SIGNAL(timeout()),this,SLOT(change_stars()));

    // start the timer
    timerStars->start(500);
}

void Wanted::increase(double n){
    wanted += n;

}

void Wanted::decrease(double n){
    wanted -= n;

}

void Wanted::reinit(){
    wanted = 0;
    setPixmap(QPixmap(":/textures/resources/textures/0-star.png"));

}

double Wanted::getWanted(){
    return wanted;
}

void Wanted::change_stars(){
    if (b)
    {
        setPixmap(QPixmap(":/textures/resources/textures/0-star.png"));
    }
    else
    {
        int nb = getWanted();
        if(nb < 10) setPixmap(QPixmap(":/textures/resources/textures/0-star.png"));
        else if(nb < 70) setPixmap(QPixmap(":/textures/resources/textures/1-star.png"));
        else if(nb < 200) setPixmap(QPixmap(":/textures/resources/textures/2-stars.png"));
        else if(nb < 500) setPixmap(QPixmap(":/textures/resources/textures/3-stars.png"));
        else if(nb < 1800) setPixmap(QPixmap(":/textures/resources/textures/4-stars.png"));
        else setPixmap(QPixmap(":/textures/resources/textures/5-stars.png"));
   }
    setOpacity(0.8);
    b = !b;
}

