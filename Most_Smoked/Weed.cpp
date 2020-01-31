#include "Weed.h"
#include <QFont>

Weed::Weed(QGraphicsItem *parent): Info(parent){
    // initialize weed to 0
    reset();

    // draw the text
    setDefaultTextColor(Qt::green);
    setFont(QFont("times",16));
    setZValue(1); // on top
}

void Weed::increase(int n){
    value += n;
    setPlainText(QString("W€€d: ") + QString::number(value));
}

void Weed::decrease(int n){
    value -= n;
    if (value < 0) reset();
    setPlainText(QString("W€€d: ") + QString::number(value));
}

void Weed::reset(){
    value = 300;
    setPlainText(QString("W€€d: ") + QString::number(value));
}


int Weed::getvalue(){
    return value;
}
