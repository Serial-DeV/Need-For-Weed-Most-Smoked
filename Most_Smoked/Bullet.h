#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QObject>
#include <QMediaPlayer>

class Bullet: public QObject,public QGraphicsRectItem{
    Q_OBJECT
public:
    Bullet(QGraphicsItem * parent=0, int n = 0);
public slots:
    void move();
private:
    int direction;
    QMediaPlayer* nanisound;
    QMediaPlayer* ughsound;
};

#endif // BULLET_H
