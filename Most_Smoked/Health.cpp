#include "Health.h"
#include <QFont>

Health::Health(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    reset();

    // draw the text
    setDefaultTextColor(Qt::red);
    setFont(QFont("times",16));
    setZValue(1); // on top
}

void Health::decrease(){
    health--;
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 2
}

void Health::increase(){
    health++;
    setPlainText(QString("Health: ") + QString::number(health)); // Health: 2
}

int Health::getHealth(){
    return health;
}

void Health::reset(){
    health = 3;
    setPlainText(QString("Health: ") + QString::number(health));
}

