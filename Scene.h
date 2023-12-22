#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include "Obstruction.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemyhealth.h"
#include "Eagle.h"
#include "Score.h"

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

public slots:
    bool collisionWithObstacle(const QPointF &nextPos, const QPointF &pos);
    void randomGenerateEnemyStart();
    void decreaseEnemyHealth();

private:
    int random_factor;
    Score *score;
    Player *player;
    QList<EnemyHealth*> enemyHealthList;
    Eagle *eagle;
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

protected:
    void keyPressEvent(QKeyEvent *event);
    //void keyPressTest(QKeyEvent *event, int status);
signals:
    void restartGame();
    void pauseGame();
    void continueGame();

};

#endif // SCENE_H
