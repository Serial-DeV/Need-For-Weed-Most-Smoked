#include "Police.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h> // rand() -> really large int
#include "Game.h"

extern Game * game;

Police::Police(QGraphicsItem *parent): Enemy(parent){
 setPixmap(QPixmap(":/textures/resources/textures/police.png"));

}



