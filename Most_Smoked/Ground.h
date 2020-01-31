#ifndef GROUND_H
#define GROUND_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Obstacle.h"

class Ground: public Obstacle{
    Q_OBJECT
public:
    Ground(QGraphicsItem * parent=0);
public slots:
};

#endif // GROUND_H
