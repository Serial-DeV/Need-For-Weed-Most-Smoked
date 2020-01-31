#ifndef POLICE_H
#define POLICE_H

#include "Enemy.h"

class Police: public Enemy{
    Q_OBJECT
public:
    Police(QGraphicsItem * parent=0);
private:
};

#endif // POLICE_H
