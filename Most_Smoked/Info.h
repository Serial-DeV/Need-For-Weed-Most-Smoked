#ifndef INFO_H
#define INFO_H

#include <QGraphicsTextItem>

class Info: public QGraphicsTextItem{
    Q_OBJECT
public:
    Info(QGraphicsItem * parent=0):QGraphicsTextItem(parent){}
    virtual void increase(int){}
    virtual void decrease(int){}
    virtual int getvalue(){return 0;}
    virtual void reset(){}
private:
    int value;
};

#endif // INFO_H
