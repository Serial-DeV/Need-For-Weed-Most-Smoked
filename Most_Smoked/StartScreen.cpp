#include "Obstacle.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"

extern Game * game;

StartScreen::StartScreen(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    setPos(0,0);
    pix = QPixmap(":/textures/resources/textures/NFW.jpg");
}

void StartScreen::resize(int w, int h)
{
    pix = pix.scaled(w, h);
    setPixmap(pix);
}
