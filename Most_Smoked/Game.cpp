#include "Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include "Enemy.h"
#include "Player.h"
#include "Police.h"
#include "Client.h"
#include "Bomb.h"
#include "Hostile.h"
#include "BulletCounter.h"
#include <QMediaPlayer>
#include <QApplication>
#include <QDesktopWidget>
#include <string.h>
#include <QDebug>


Game::Game(QWidget *parent){
    // create the scene
    bombIsPresent = false;
    scene = new QGraphicsScene();

    QDesktopWidget dw;

    //+2 pour masquer les bordures
    win_h = dw.height()+2;
    win_w = dw.width()+2;

    qDebug() << "height: " << win_h << " * width: "<< win_w << "\n";
    ceiling = win_h/2-96;
    floor = win_h/2+96;
    QWidget::showFullScreen();
    QWidget::move(-1,-1);
    scene->setSceneRect(0,0,win_w, win_h);

    // make the newly created scene the scene to visualize (since Game is a QGraphicsView Widget,
    // it can be used to visualize scenes)
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(win_w,win_h);


    // For a better "random" (each 1st game after launch will be different)
    srand (time(NULL));

    // create the player
    player = new Player();
    player->setPos(win_w/2,win_h/2);
    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    // add the player to the scene
    scene->addItem(player);
    // holds whether clicking into the scene background will clear focus
    scene->setStickyFocus(player);

    obstacles = new Obstacle*();
    int c = 0;
    for (int w = 0; w < win_w; w+=32)
    {
        for (int h = 0; h < win_h; h+=32)
        {
            if((h < ceiling))
            {
                obstacles[c] = new Obstacle();
                obstacles[c]->setPos(w, h);
                scene->addItem(obstacles[c]);
            }
        }
    }


    ground = new Ground*();
    int c2 = 0;
    for (int w = 0; w < win_w; w+=32)
    {
        for (int h = floor; h < win_h; h+=32)
        {

            ground[c2] = new Ground();
            ground[c2]->setPos(w, h);
            scene->addItem(ground[c2]);

        }
    }


    // add the money
    player->get_money()->setPos(player->get_money()->x(),player->get_money()->y()+50);
    scene->addItem(player->get_money());
    // add the weed
    player->get_weed()->setPos(player->get_money()->x(),player->get_money()->y()+50);
    scene->addItem(player->get_weed());
    // add the wanted level
    player->get_wanted()->setPos(player->get_wanted()->x()+(win_w - 280),player->get_wanted()->y()+10);
    scene->addItem(player->get_wanted());

    // create the score/health
    scene->addItem(player->get_score());
    player->get_health()->setPos(player->get_health()->x(),player->get_health()->y()+25);
    scene->addItem(player->get_health());

    // add the amount of remaining bullets
    player->get_bulletcounter()->setPos(player->get_bulletcounter()->x(),player->get_bulletcounter()->y()+75);
    scene->addItem(player->get_bulletcounter());

    player->next_level->setPlainText(QString(" / 4         Level 1"));
    player->next_level->setPos(50,0);
    player->next_level->setDefaultTextColor(Qt::blue);
    player->next_level->setFont(QFont("times",16));
    player->next_level->setZValue(1);
    scene->addItem(player->next_level);

    nbEnemy = 0;
    nbClient = 0;

    startscreen = new StartScreen();
    scene->addItem(startscreen);
    startscreen->resize(win_w, win_h);
    startscreen->setZValue(1);
    startscreen_message = new QGraphicsTextItem();
    startscreen_message->setPlainText(QString("Press enter to start or escape to quit"));
    startscreen_message->setFont(QFont("times",25));
    startscreen_message->setDefaultTextColor(Qt::green);
    startscreen_message->setPos(win_w/2.65,win_h/1.1);
    scene->addItem(startscreen_message);
    startscreen_message->setZValue(1);
    startscreen_on = true;

    show();
}

void Game::removeEnemies()
{
    for (vector<Enemy*>::iterator it = enemies.begin(); it < enemies.end(); it++)
    {
        scene->removeItem(*it);
    }
    (enemies).erase((enemies).begin(), (enemies).end());
    nbEnemy = 0;
}

void Game::removeClients()
{
    for (vector<Client*>::iterator it = clients.begin(); it < clients.end(); it++)
    {
        scene->removeItem(*it);
    }
    (clients).erase((clients).begin(), (clients).end());
    nbClient = 0;
}

