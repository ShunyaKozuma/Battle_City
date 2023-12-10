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

public slots:
    bool collisionWithObstacle(const QPointF &nextPos, const QPointF &pos);

private:
    Player *player;
    Brick *brick;
    QTimer *timer;
    Qt::Key currentDirection;
    bool advance = true;

protected:
    void keyPressEvent(QKeyEvent *event);
    //void keyPressTest(QKeyEvent *event, int status);
};

#endif // SCENE_H
