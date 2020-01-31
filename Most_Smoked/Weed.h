#ifndef WEED_H
#define WEED_H

#include "Info.h"

class Weed: public Info{
public:
    Weed(QGraphicsItem * parent=0);
    void increase(int);
    void decrease(int);
    int getvalue();
    void reset();
private:
    int value;
};

#endif // WEED_H
