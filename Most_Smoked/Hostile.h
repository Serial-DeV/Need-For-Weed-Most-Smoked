#ifndef HOSTILECPP_H
#define HOSTILECPP_H


#include "Enemy.h"

class Hostile: public Enemy{
    Q_OBJECT
public:
    Hostile(QGraphicsItem * parent=0);
private slots:
    void move();
private:
};

#endif // HOSTILECPP_H
