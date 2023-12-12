#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include "Obstruction.h"
#include "Brick.h"
#include "Steel.h"
#include "Bullet.h"
#include "Player.h"
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
    // //////////////////////////
    void startGame();

    bool getGameOn() const;
    void setGameOn(bool newGameOn);
    // ///////////////////////////

public slots:
    bool collisionWithObstacle(const QPointF &nextPos, const QPointF &pos);

private:
    Player *player;
    Brick *brick;
    QTimer *timer;
    Qt::Key currentDirection;
    bool advance = true;
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
