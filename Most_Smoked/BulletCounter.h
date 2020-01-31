#ifndef BULLETCOUNTER_H
#define BULLETCOUNTER_H

#include <QGraphicsTextItem>

class BulletCounter: public QGraphicsTextItem{
public:
    BulletCounter(QGraphicsItem * parent=0);
    int get_bullets();
    void init_bullets();
    void increase_bullets(int);
    void decrease_bullets();

    BulletCounter& operator++ (int)
    {
        bullet_amount += 2;
        return *this;
    }

    BulletCounter& operator++()
    {
        bullet_amount += 2;
        return *this;
    }


private:
    int bullet_amount;
};
#endif // BULLETCOUNTER_H
