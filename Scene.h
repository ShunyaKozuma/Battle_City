#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include<QElapsedTimer>
#include <QList>
#include "Obstruction.h"
#include "Brick.h"
#include "Steel.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include <QGraphicsScene>

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
    //void LiveMinus();
    //Basic *basic;

public slots:
    bool collisionWithObstacle(const QPointF &nextPos, const QPointF &pos);
    //void LiveMinus();

private slots:
    //void updateTimer();
    void UpdateGameTimer();

private:
    Player *player;
    Brick *brick;
    Basic *basic;
    Fast *fast;
    Power *power;
    Armor *armor;
    QTimer *timer;
    Qt::Key currentDirection;
    bool advance = true;
    //widget control
    bool gameOn;
    int CurrentStatus=1;//偵測目前狀態，1為遊戲處於封面狀態；2為遊戲處於進行狀態；3為遊戲處於暫停狀態；4為遊戲處於結束遊戲畫面狀態(尚未處理)

    //關於計時器的
    QTimer *updateTimer;
    QElapsedTimer *gametimer;
    QGraphicsTextItem *timerDisplay;
    qint64 pausedTime;


protected:
    void keyPressEvent(QKeyEvent *event);
    //void keyPressTest(QKeyEvent *event, int status);
signals:
    void restartGame();
    void pauseGame();
    void continueGame();

};

#endif // SCENE_H
