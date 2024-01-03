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
#include "PowerUp.h"
#include<QElapsedTimer>
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
    void freezeAllItem();
    void defreezeAllItem();
    QPointF detectIceCollision(const QPointF &nextPos, const QPointF &pos,int playernum=1);
    void saveAllRecord();
    void getOldRecord();


    //




public slots:
    bool collisionWithObstacle(const QPointF &nextPos, const QPointF &pos,int playernum=1);
    void randomGenerateEnemyStart();
    void decreaseEnemyHealth();
    void LosePLayerToScene();
    void getPowerUps();
    void usePowerUps(const PowerUp::PowerUpType type);
    void UpdateGameTimer();
    void setCPBnull();
    void increaseScore(int);

private:
    int player_health=3;
    int player_status=1;
    int player_bulletspeedbuff=1;
    bool player_bulletpowerbuff=false;
    int random_factor;
    int background_num[HEIGHT][WIDTH];
    Player_Bullet *currentplayerbullet=nullptr;
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
    Flashing *flashing;
    QTimer *timer;
    Qt::Key currentDirection;
    Qt::Key currentDirection2;

    bool player_conti_shoot=false;
    int player_bullet_max=0;

    bool advance = true;
    //widget control
    bool gameOn;
    int CurrentStatus=1;//偵測目前狀態，1為遊戲處於封面狀態；2為遊戲處於進行狀態；3為遊戲處於暫停狀態；4為遊戲處於結束遊戲畫面狀態(尚未處理)
    int gameLevel=2;//關卡變數1:第一關2: 第二關
    int playerNumber=1;
    int tanknum = 0;
    int enemyLife = tanknum;
    QString resourcePath;
    QString saveRecordPath;
    int bulletvar;


    //關於計時器的
    QTimer *updateTimer;
    QTimer *invinciable;
    QTimer *star_timer;
    QGraphicsTextItem *timerDisplay;
    QGraphicsTextItem *healthDisplay;
    QGraphicsTextItem *InvincibleDisplay;
    QTimer *bulletTimer;
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
