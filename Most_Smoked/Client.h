#ifndef CLIENT_H
#define CLIENT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include "Person.h"

class Client: public Person{
    Q_OBJECT
public:
    Client(QGraphicsItem * parent=0);
public slots:
    void move(){}
};

#endif // CLIENT_H
