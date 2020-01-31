#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Enemy.h"
#include "Police.h"
#include "Hostile.h"
#include "Client.h"
#include "Game.h"
#include "vector"
#include "Bomb.h"
#include "QTime"
#include "qcoreapplication.h"
#include "math.h"
#include "QBuffer"

#define lvinfinite 1000000
#define lv20 777
#define lv19 666
#define lv18 505
#define lv17 404
#define lv16 320
#define lv15 250
#define lv14 195
#define lv13 150
#define lv12 130
#define lv11 115
#define lv10 95
#define lv9 75
#define lv8 60
#define lv7 42
#define lv6 30
#define lv5 20
#define lv4 13
#define lv3 8
#define lv2 4

#include <QDebug>
extern Game * game;

void delay(int n);
void load_sound(const QString &s,QMediaPlayer * sound);

Player::Player(QGraphicsItem *parent):Person(parent){
    // play background music
    musicgame = new QMediaPlayer();
    musicrestart = new QMediaPlayer();
    musicstart = new QMediaPlayer();
    musicstart->setMedia(QUrl("qrc:/musics/resources/musics/RidersOnTheStorm.mp3"));
    musicgame->setMedia(QUrl("qrc:/musics/resources/musics/warsongs_PiercingLight(MakoRemix)Music-LeagueofLegends.mp3"));
    musicrestart->setMedia(QUrl("qrc:/musics/resources/musics/baki_2018_OST_Tension.mp3"));


    musicstart->play();

    exit_asked = false;

    can_shoot = true;

    money = new Money();
    wanted = new Wanted();
    weed = new Weed();
    score= new Score();
    health = new Health();
    next_level = new QGraphicsTextItem();
    bulletcounter = new BulletCounter();
    setPixmap(QPixmap(":/textures/resources/textures/player2.png"));
    saveX = x();
    saveY = y();
    alive = false;
    level = 1;
    cashsound = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    bulletsound = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    levelupsound = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    oofsound = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    wasted = new QMediaPlayer(this, QMediaPlayer::LowLatency);
    quitsound = new QMediaPlayer(this, QMediaPlayer::LowLatency);

    load_sound(":/sounds/resources/sounds/SmokeWeedEveryday.ogg", quitsound);
    load_sound(":/sounds/resources/sounds/bullet.ogg", bulletsound);
    load_sound(":/sounds/resources/sounds/cash.ogg", cashsound);
    load_sound(":/sounds/resources/sounds/oof.ogg", oofsound);
    levelupsound->setMedia(QUrl("qrc:/sounds/resources/sounds/levelup.ogg"));
    wasted->setMedia(QUrl("qrc:/sounds/resources/sounds/wasted.ogg"));


    restart_message = new QGraphicsTextItem();
    restart_message->setPlainText(QString("Press enter to restart or escape to start screen"));
    restart_message->setFont(QFont("times",25));

    restart_asked = false;
    restart_is_on = false;


    finalTimer = new QTimer(this);
    QObject::connect(finalTimer,SIGNAL(timeout()),this,SLOT(printRestart()));

    startTimer = new QTimer(this);
    QObject::connect(startTimer,SIGNAL(timeout()),this,SLOT(printStart()));
    startTimer->start(1000);

    this->installEventFilter(this);

    QTimer * timerMove = new QTimer(this);
    QObject::connect(timerMove,SIGNAL(timeout()),this,SLOT(move()));
    timerMove->start(10);

    QTimer * collisionChecker = new QTimer(this);
    QObject::connect(collisionChecker,SIGNAL(timeout()),this,SLOT(checkCollidingItems()));
    collisionChecker->start(1);


    // spawn enemies and clients
    QTimer * timer = new QTimer(this);
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(spawn()));
    timer->start(2000);

    QTimer * timerBomb = new QTimer(this);
    QObject::connect(timerBomb,SIGNAL(timeout()),this,SLOT(spawnBomb()));
    timerBomb->start(2000);

    shoot_timer = new QTimer(this);
    QObject::connect(shoot_timer,SIGNAL(timeout()),this,SLOT(set_can_shoot()));


    goLeft = false;
    goRight = false;


}

void load_sound(const QString &s, QMediaPlayer * sound)
{
    QFile file(s);
    file.open(QIODevice::ReadOnly);
    QByteArray *ba = new QByteArray();
    ba->append(file.readAll());
    QBuffer *buffer = new QBuffer(ba);
    buffer->open(QIODevice::ReadOnly);
    buffer->reset();  // same as buffer.seek(0);
    qDebug() << "Buffer size:" << buffer->size(); // is the file loaded
    sound->setMedia(QMediaContent(), buffer);
}

void Player::set_can_shoot()
{
    shoot_timer->stop();
    can_shoot = true;
}

Money* Player::get_money()
{
    return money;
}

Weed* Player::get_weed()
{
    return weed;
}

Score* Player::get_score()
{
    return score;
}

Health* Player::get_health()
{
    return health;
}

Wanted* Player::get_wanted()
{
    return wanted;
}

BulletCounter* Player::get_bulletcounter()
{
    return bulletcounter;
}


void Player::move()
{
    bool obstacleIsPresent;

    if(alive && goLeft && pos().x() > 0)
    {
        setPos(x()-1.5,y());
        obstacleIsPresent = checkObstacle();
    }

    if(alive && goRight && pos().x() + PLAYER_LENGTH < game->win_w)
    {
        setPos(x()+1.5,y());
        obstacleIsPresent = checkObstacle();
    }

}

void Player::checklevel()
{
    if(score->getScore() == lv20)
    {
        money->increase(20000);
        level = 20;
        health->increase();
        bulletcounter->increase_bullets(1000);
        change_level(lvinfinite);
    }

    else if(score->getScore() == lv19)
    {
        money->increase(10000);
        level = 19;
        health->increase();
        bulletcounter->increase_bullets(200);
        change_level(lv20);
    }
    else if(score->getScore() == lv18)
    {
        money->increase(5000);
        level = 18;
        health->increase();
        bulletcounter->increase_bullets(100);
        change_level(lv19);
    }
    else if(score->getScore() == lv17)
    {
        money->increase(4000);
        level = 17;
        health->increase();
        bulletcounter->increase_bullets(50);
        change_level(lv18);
    }
    else if(score->getScore() == lv16)
    {
        money->increase(3000);
        level = 16;
        health->increase();
        bulletcounter->increase_bullets(50);
        change_level(lv17);
    }
    else if(score->getScore() == lv15)
    {
        money->increase(2000);
        level = 15;
        health->increase();
        bulletcounter->increase_bullets(50);
        change_level(lv16);
    }
    else if(score->getScore() == lv14)
    {
        money->increase(1000);
        level = 14;
        change_level(lv15);
    }
    else if(score->getScore() == lv13)
    {
        money->increase(900);
        level = 13;
        change_level(lv14);
    }
    else if(score->getScore() == lv12)
    {
        money->increase(800);
        level = 12;
        change_level(lv13);
    }
    else if(score->getScore() == lv11)
    {
        money->increase(700);
        level = 11;
        change_level(lv12);
    }
    else if(score->getScore() == lv10)
    {
        money->increase(600);
        level = 10;
        health->increase();
        bulletcounter->increase_bullets(50);
        change_level(lv11);
    }
    else if(score->getScore() == lv9)
    {
        money->increase(500);
        level = 9;
        change_level(lv10);
    }
    else if(score->getScore() == lv8)
    {
        money->increase(400);
        level = 8;
        change_level(lv9);
    }
    else if(score->getScore() == lv7)
    {
        money->increase(300);
        level = 7;
        change_level(lv8);
    }
    else if(score->getScore() == lv6)
    {
        money->increase(200);
        level = 6;
        change_level(lv7);
    }
    else if(score->getScore() == lv5)
    {
        money->increase(100);
        level = 5;
        health->increase();
        bulletcounter->increase_bullets(50);
        change_level(lv6);
    }
    else if(score->getScore() == lv4)
    {
        money->increase(70);
        level = 4;
        change_level(lv5);
    }
    else if(score->getScore() == lv3)
    {
        money->increase(50);
        level = 3;
        change_level(lv4);
    }
    else if(score->getScore() == lv2)
    {
        money->increase(30);
        level = 2;
        change_level(lv3);
    }
    else if(score->getScore() == 0)
    {
        level = 1;
        change_level(lv2);
    }

    else if(score->getScore() == 10)
    {
        change_level(lv4);
    }
    else if(score->getScore() == 100)
    {
        change_level(lv11);
    }

    else if(score->getScore() == 1000)
    {
        change_level(lvinfinite);
    }

}

void Player::change_level(int lv)
{
    if(level != 1)
    levelupsound->play();
    game->scene->removeItem(next_level);
    if (score->getScore() < 10)
    {
        next_level->setPlainText(QString(" / ") + QString::number(lv) + QString("         Level ") + QString::number(level));
        next_level->setPos(50,0);
    }

    else if(score->getScore() < 100)
    {
        next_level->setPlainText(QString(" / ") + QString::number(lv) + QString("         Level ") + QString::number(level));
        next_level->setPos(60,0);
    }

    else if (score->getScore() < 1000)
    {
        next_level->setPlainText(QString(" / ") + QString::number(lv) + QString("         Level ") + QString::number(level));
        next_level->setPos(70,0);
    }

    else if (score->getScore() < 10000)
    {
        next_level->setPlainText(QString(" / ") + QString::number(lv) + QString("         Level ") + QString::number(level));
        next_level->setPos(80,0);
    }


    game->scene->addItem(next_level);
}


bool Player::eventFilter(QObject * obj, QEvent * event)
{
    if(event->type()==QEvent::KeyRelease)
    {
        pressedKeys -= ((QKeyEvent*)event)->key();
        if (((QKeyEvent*)event)->key() == 16777234)
        {
            goLeft = false;
        }

        else if (((QKeyEvent*)event)->key() == 16777236)
        {
            goRight = false;
        }
    }

    if(event->type()==QEvent::KeyPress) {
        saveX = x();
        saveY = y();
        pressedKeys += ((QKeyEvent*)event)->key();
        bool ground = checkGround();


        if( alive && pressedKeys.contains(Qt::Key_Space) && ground && pos().y() > 0)
        {
            Person::gForce = -6 ;
        }

        if( pressedKeys.contains(Qt::Key_Right) && pressedKeys.contains(Qt::Key_Left))
        {
            goRight = false;
            goLeft = false;
        }
        else if( pressedKeys.contains(Qt::Key_Left) && pos().x() > 0)
        {
            goLeft = true;
            goRight = false;
        }
        else if( pressedKeys.contains(Qt::Key_Right) && pos().x() + PLAYER_LENGTH < game->win_w)
        {
            goRight = true;
            goLeft = false;
        }






        // shoot right with D
        if (pressedKeys.contains(Qt::Key_D) && bulletcounter->get_bullets() > 0 && can_shoot){

            can_shoot = false;
            shoot_timer->start(500);

//             play bulletsound
            if (bulletsound->state() == QMediaPlayer::PlayingState)
            {
                bulletsound->setPosition(0);
            }
            else bulletsound->play();

            // D creates a bullet
            Bullet * bullet = new Bullet(0,6);
            bulletcounter->decrease_bullets();
            bullet->setPos(x(),y());
            scene()->addItem(bullet);
            wanted->increase(0.2);
        }

        // shoot left with A or Q
        else if ((pressedKeys.contains(Qt::Key_A) || pressedKeys.contains(Qt::Key_Q)) && bulletcounter->get_bullets() > 0 && can_shoot){

            can_shoot = false;
            shoot_timer->start(500);

//            // play bulletsound
            if (bulletsound->state() == QMediaPlayer::PlayingState)
            {
                bulletsound->setPosition(0);
            }
            else bulletsound->play();

            // Q or A create a bullet
            Bullet * bullet = new Bullet(0,4);
            bulletcounter->decrease_bullets();
            bullet->setPos(x(),y());
            scene()->addItem(bullet);
            wanted->increase(0.2);


        }

    }
    return false;
}


void Player::keyReleaseEvent(QKeyEvent *event)
{

    if (alive)
    eventFilter(this,event);

    else if( restart_asked && event->key() == Qt::Key_Escape)
    {
        musicrestart->stop();
        musicstart->play();
        restart_asked = false;
        game->startscreen_on = true;
        game->startscreen->setOpacity(100);
        game->startscreen_message->setZValue(2);
        restart_asked = false;
        health->reset();
        score->reset();
        weed->reset();
        money->reset();
        level = 1;
        checklevel();
        bulletcounter->init_bullets();
        if(restart_message) game->scene->removeItem(restart_message);
        finalTimer->stop();
        final_score->setOpacity(0);
        next_level->setOpacity(0);
        game->removeEnemies();
        game->removeClients();
        pressedKeys -= Qt::Key_Left;
        pressedKeys -= Qt::Key_Right;
        pressedKeys -= Qt::Key_Space;
        goRight = false;
        goLeft = false;
        Person::gForce = 4;
    }
    else if( restart_asked && event->key() == Qt::Key_Return)
    {
        musicrestart->stop();
        musicgame->play();
        restart_asked = false;
        health->reset();
        score->reset();
        weed->reset();
        money->reset();
        level = 1;
        checklevel();
        bulletcounter->init_bullets();
        if(restart_message) game->scene->removeItem(restart_message);
        finalTimer->stop();
        final_score->setOpacity(0);
        game->removeEnemies();
        game->removeClients();
        pressedKeys -= Qt::Key_Left;
        pressedKeys -= Qt::Key_Right;
        pressedKeys -= Qt::Key_Space;
        goRight = false;
        goLeft = false;
        Person::gForce = 4;
        alive = true;
    }
    else if (!exit_asked && game->startscreen_on && event->key() == Qt::Key_Return)
    {
        musicstart->stop();
        musicgame->play();
        game->startscreen->setOpacity(0);
        game->startscreen_message->setZValue(-1);
        alive = true;
        game->startscreen_on = false;
        next_level->setOpacity(100);

    }

    else if (event->key() == Qt::Key_Escape && game->startscreen_on)
    {
      exit_asked = true;
      startTimer->stop();
      if(game->startscreen_message_on)
      game->scene->removeItem(game->startscreen_message);

      musicstart->setVolume(50);
      game->startscreen_message->setPlainText(QString("Bye! Smoke you later!"));
      game->scene->addItem(game->startscreen_message);
      game->startscreen_message->setPos(game->win_w/2.4,game->win_h/1.1);
      QTimer::singleShot(100, this, SLOT(play_quit()));

    }
}

void Player::play_quit()
{
    quitsound->play();
    musicstart->setVolume(10);
    QTimer::singleShot(3000, this, SLOT(close_window()));
}

void Player::close_window()
{
    exit(0);
}


void Player::keyPressEvent(QKeyEvent *event){
    if (alive)
    eventFilter(this,event);
}

void Player::checkCollidingItems()
{
    if (alive){
    QList<QGraphicsItem *> colliding_items = collidingItems();


    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Bomb)){

            // remove them from the scene (still on the heap)
            scene()->removeItem(colliding_items[i]);

            // delete them from the heap to save memory
            delete colliding_items[i];
            game->bombIsPresent = false;
            game->removeEnemies();
            return;
        }
    }

    for (int i = 0, n = colliding_items.size(); i < n; ++i){
    // if one of the colliding items is a Client, destroy the Client and increase score
        if (typeid(*(colliding_items[i])) == typeid(Client)){

            // play cashsound
            if (cashsound->state() == QMediaPlayer::PlayingState)
            {
                cashsound->setPosition(0);
            }
            else cashsound->play();

            // increase the score
            score->increase();

            // remove them from the scene
            scene()->removeItem(colliding_items[i]);

            game->nbClient--;
            weed->decrease(1);
            // return (all code below refers to a non existint bullet)
            money->increase(10);
            wanted->increase(1);
            checklevel();
            if (weed->getvalue() == 0)
            {
                end_of_game();
            }

            return;
        }

         // if one of the colliding items is an Enemy, destroy the Enemy and decrease health
        if (typeid(*(colliding_items[i])) == typeid(Police) || typeid(*(colliding_items[i])) == typeid(Hostile))
        {
           // play oofsound
            if (oofsound->state() == QMediaPlayer::PlayingState)
            {
                oofsound->setPosition(0);
            }
            else oofsound->play();

            // decrease the health
            health->decrease();
            // reinitialisation of the wanted level
            wanted->reinit();

            game->removeEnemies();
            if (!health->getHealth())
            {
                end_of_game();
            }
            return;
        }
    }
    }
}

void Player::end_of_game()
{
    alive = false;
    // play wastedsound
    if (wasted->state() == QMediaPlayer::PlayingState)
    {
        wasted->setPosition(0);
    }
    else wasted->play();

    delay(4000);

    // change background music
    musicrestart->play();
    musicgame->stop();

    restart_message->setPos(400,game->win_h/2);
    final_score = new Score();
    final_score->setDefaultTextColor(Qt::blue);
    final_score->setFont(QFont("times",25));
    setZValue(1); // on top

    if (weed->getvalue() == 0) final_score->setPlainText(QString("Final score: score + bullets + money + 100 * health"));
    else final_score->setPlainText(QString("Final score: score + bullets + money + w€€d"));
    final_score->setPos(400,game->win_h/2 - 64);
    game->scene->addItem(final_score);

    delay(2000);
    game->scene->removeItem(final_score);

    int sc = score->getScore();
    int bull = bulletcounter->get_bullets();
    int mon = money->getvalue();
    int h = 100 * health->getHealth();
    int w = weed->getvalue();
    int tot = sc + bull + mon + h + w;

    if (weed->getvalue() == 0) final_score->setPlainText(QString("Final score: ") + QString::number(sc) + QString(" + ") + QString::number(bull) + QString(" + ") + QString::number(mon) + QString(" + ") + QString::number(h));
    else final_score->setPlainText(QString("Final score: ") + QString::number(sc) + QString(" + ") + QString::number(bull) + QString(" + ") + QString::number(mon) + QString(" + ") + QString::number(w));
    final_score->setPos(final_score->x(),final_score->y());
    game->scene->addItem(final_score);

    delay(2000);

    int tmp = 1;
    int cpt = 0;
    while (cpt < tot)
    {
        if (tot - cpt > 100) tmp = 1;
        else if (tot - cpt > 50) tmp = 50;
        else if (tot - cpt > 20) tmp = 75;
        else if (tot - cpt > 10) tmp = 100;
        else if (tot - cpt > 5) tmp = 200;
        else if (tot - cpt > 3) tmp = 300;
        else if (tot - cpt > 2) tmp = 400;
        else if (tot - cpt > 1) tmp = 600;
        else tmp = 1500;

        delay(tmp);
        cpt++;

        game->scene->removeItem(final_score);
        final_score->setPlainText(QString("Final score: ") + QString::number(cpt));
        final_score->setPos(final_score->x(),final_score->y());
        game->scene->addItem(final_score);
    }



    finalTimer->start(1000);
    restart_asked = true;
}

void Player::printRestart(){


    if (!restart_is_on){
        game->scene->addItem(restart_message);
        restart_is_on = true;
    }
    else {
        game->scene->removeItem(restart_message);
        restart_is_on = false;
    }

}

void Player::printStart(){

    if(game->startscreen_on)
    {
        if (!game->startscreen_message_on){
            game->scene->addItem(game->startscreen_message);
            game->startscreen_message_on = true;
        }
        else {
            game->scene->removeItem(game->startscreen_message);
            game->startscreen_message_on = false;
        }
    }

}


void delay(int n)
{
    QTime dieTime= QTime::currentTime().addMSecs(n);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

void Player::spawn(){
    // create Police
    if (alive){
        if (game->nbEnemy <= get_wanted()->getWanted()/100)
        {
        Police * police = new Police();
        game->enemies.push_back(police);
        scene()->addItem(police);
        game->nbEnemy++;
        }

        if (game->nbClient <= 1)
        {
        Client * client = new Client();
        game->clients.push_back(client);
        scene()->addItem(client);
        game->nbClient++;
        }
    }
}



void Player::spawnBomb(){
    if (alive && !(game->bombIsPresent) && game->nbEnemy > 5 && (rand() % 5 ) >= 4 )
    {
    Bomb * bomb = new Bomb();
    scene()->addItem(bomb);
    game->bombIsPresent = true;
    }
}

void Player::unconditional_spawn(int x, int y)
{
    Hostile * h = new Hostile();
    game->enemies.push_back(h);
    h->setPos(x,y);
    scene()->addItem(h);
    game->nbEnemy++;
}
