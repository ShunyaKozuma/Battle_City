#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <QPair>
#include "Obstruction.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemyhealth.h"
#include "Eagle.h"
#include "Score.h"
#include<QElapsedTimer>
#include "Item.h"
#define WIDTH 26
#define HEIGHT 28
#define BLOCKUNIT 25

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    ~Scene();
    //widget control
    void startGame();
    bool getGameOn() const;
    void setGameOn(bool newGameOn);
    void BeforeNextPage();
    void AddOnePlayer();
    QList<QPair<int, int>> ScoreRecord;
    int Player2Exist=0;

public slots:
    bool collisionWithObstacle(const QPointF &nextPos, const QPointF &pos,int playernum=1);
    void randomGenerateEnemyStart();
    void decreaseEnemyHealth();
    void LosePLayerToScene();
private slots:
    //void updateTimer();
    void UpdateGameTimer();
private:
    int random_factor;
    Score *score;
    Player *player;
    Player *player2;
    QList<EnemyHealth*> enemyHealthList;
    Eagle *eagle;
    Brick *brick;
    Steel *steel;
    Trees *tree;
    Water *water;
    Ice *ice;
    Basic *basic;
    Fast *fast;
    Power *power;
    Armor *armor;
    QTimer *timer;
    Qt::Key currentDirection;
    Qt::Key currentDirection2;
    //buff
    Grenade *grenade;
    Helmet *helmet;
    Shovel *shovel;
    Tank *tank;
    Star *star;
    SpecialTimer *specialTimer;

    bool advance = true;
    //widget control
    bool gameOn;
    int CurrentStatus=1;//偵測目前狀態，1為遊戲處於封面狀態；2為遊戲處於進行狀態；3為遊戲處於暫停狀態；4為遊戲處於結束遊戲畫面狀態(尚未處理)
    int tanknum;


    //關於計時器的
    QTimer *updateTimer;
    QGraphicsTextItem *timerDisplay;
    int totalplaytime=0;
    void AddNewRecord();


protected:
    void keyPressEvent(QKeyEvent *event);
    //void keyPressTest(QKeyEvent *event, int status);
signals:
    void restartGame();//傳遞全部重頭開始直接回到初始介面
    void pauseGame();//傳遞玩到一半要暫停介面
    void continueGame();//傳遞暫停後要繼續遊戲畫面
    void finishGame();//傳遞關卡成功後過度畫面
    void GameOver();//傳遞遊戲失敗結束畫面

};

#endif // SCENE_H
