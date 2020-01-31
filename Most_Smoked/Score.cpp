#include "Score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent): QGraphicsTextItem(parent){
    // initialize the score to 0
    reset();

    // draw the text
    setDefaultTextColor(Qt::blue);
    setFont(QFont("times",16));
    setZValue(1); // on top
}

void Score::increase(){
    score++;
    setPlainText(QString("XP: ") + QString::number(score)); // Score+1
}

int Score::getScore(){
    return score;
}
void Score::reset(){
    score = 0;
    setPlainText(QString("XP: ") + QString::number(score)); // Score: 0
}
