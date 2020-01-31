#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class StartScreen: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    StartScreen(QGraphicsItem * parent=0);
    void resize(int, int);
private:
    QPixmap pix;
};

#endif // STARTSCREEN_H
