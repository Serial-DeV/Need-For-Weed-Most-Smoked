#ifndef PERSON_H
#define PERSON_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Person:public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Person(QGraphicsItem * parent=0);
public slots:
    void gravity();
protected:
    bool checkObstacle();
    bool checkGround();
    double gForce;
    double saveX;
    double saveY;

};

#endif // PERSON_H
