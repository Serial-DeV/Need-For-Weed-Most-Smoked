#ifndef MONEY_H
#define MONEY_H

#include "Info.h"

class Money: public Info{
public:
    Money(QGraphicsItem * parent=0);
    void increase(int);
    void decrease(int);
    int getvalue();
    void reset();
private:
    int value;
};

#endif // MONEY_H
