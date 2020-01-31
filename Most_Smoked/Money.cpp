#include "Money.h"
#include <QFont>

Money::Money(QGraphicsItem *parent): Info(parent){
    // initialize money to 0
    reset();

    // draw the text
    setDefaultTextColor(Qt::green);
    setFont(QFont("times",16));
    setZValue(1); // on top
}

void Money::increase(int n){
    value += n;
    setPlainText(QString("Money: ") + QString::number(value));
}

void Money::decrease(int n){
    value -= n;
    if (value < 0) reset();
    setPlainText(QString("Money: ") + QString::number(value));
}

void Money::reset(){
    value = 0;
    setPlainText(QString("Money: ") + QString::number(value));
}


int Money::getvalue(){
    return value;
}
