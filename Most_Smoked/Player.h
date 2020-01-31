#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QSet>
#include "Person.h"
#include "Score.h"
#include "Money.h"
#include "Wanted.h"
#include "Weed.h"
#include "Score.h"
#include "Health.h"
#include "BulletCounter.h"
#include <QMediaPlayer>


class Player:public Person{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event);
    Money* get_money();
    Wanted* get_wanted();
    Weed* get_weed();
    Score* get_score();
    Health* get_health();
    BulletCounter* get_bulletcounter();
    void unconditional_spawn(int, int);
    void end_of_game();
    void checklevel();
    void change_level(int);
    QGraphicsTextItem * next_level;
public slots:
    void spawnBomb();
    void spawn();
    void move();
    void checkCollidingItems();
    void printRestart();
    void set_can_shoot();
    void printStart();
    void play_quit();
    void close_window();
private:
    Money * money;
    Wanted * wanted;
    Weed * weed;
    int key[4];
    bool eventFilter(QObject * obj, QEvent * event);
    QSet<int> pressedKeys;
    void keyReleaseEvent(QKeyEvent *event);
    bool directions[0];
    double gForce;
    bool goLeft;
    bool goRight;
    bool restart_asked;
    bool alive;
    Score * final_score;
    QGraphicsTextItem * restart_message;
    bool restart_is_on;
    QTimer * finalTimer;
    QTimer * startTimer;
    Score * score;
    Health * health;
    BulletCounter * bulletcounter;
    int level;
    QMediaPlayer * musicgame;
    QMediaPlayer * musicrestart;
    QMediaPlayer * musicstart;
    QMediaPlayer* quitsound;
    QMediaPlayer* bulletsound;
    QMediaPlayer* cashsound;
    QMediaPlayer* levelupsound;
    QMediaPlayer* oofsound;
    QMediaPlayer* wasted;
    QTimer * shoot_timer;
    bool can_shoot;
    bool exit_asked;



};

#endif // PLAYER_H
