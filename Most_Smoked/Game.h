#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <vector>
#include <list>
#include "Player.h"
#include "Enemy.h"
#include "Client.h"
#include "Obstacle.h"
#include "Ground.h"
#include "StartScreen.h"
#define PLAYER_LENGTH 10
#define PLAYER_WIDTH 10


using namespace std;

class Game: public QGraphicsView{
public:
    Game(QWidget * parent=0);
    QGraphicsScene * scene;
    Player * player;
    int nbEnemy;
    int nbClient;
    vector<Enemy*> enemies;
    vector<Client*> clients;
    bool bombIsPresent;
    Obstacle **obstacles;
    Ground **ground;
    void removeEnemies();
    void removeClients();
    int win_w;
    int win_h;
    int ceiling;
    int floor;
    StartScreen* startscreen;
    QGraphicsTextItem * startscreen_message;
    bool startscreen_on;
    bool startscreen_message_on;


};

#endif // GAME_H
