#ifndef WANTED_H
#define WANTED_H

#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class Wanted:public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Wanted(QGraphicsItem * parent=0);
    void increase(double);
    void decrease(double);
    double getWanted();
    void reinit();
private slots:
    void change_stars();
private:
    double wanted;
    bool b;
};

#endif // WANTED_H
