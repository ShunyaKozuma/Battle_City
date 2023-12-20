#ifndef ENEMY_H
#define ENEMY_H


#include <QTimer>
#include <QObject>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include"Bullet.h"

//the step of enemy tank
#define STEP 5

class Enemy :public QObject ,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation )

public:
    qreal rotation() const;
    void setRotation(qreal newRotation);
    void shootbullet(int i);
    //std::vector<Enemy_Bullet*> StoreBulletSpace;//儲存射出去的子彈的空間



public slots:
    virtual void move()=0;
    virtual void straightmove()=0;
    bool enemy_collisionWithObstacle(const QPointF &nextPos, const QPointF &pos);
    void needshootbullet();


signals:
    void enemyHitsTheGrounds(Enemy *enemy);

protected:
    QTimer *timer;
    int dir;
    const QList<QPointF> directionList = {QPointF(-STEP, 0), QPointF(0, STEP), QPointF(STEP, 0), QPointF(0, -STEP)};
    //std::vector<Enemy_Bullet*> StoreBulletSpace;//儲存射出去的子彈的空間

private:
    qreal m_rotation;
    //
protected:
    QTimer *shoot_timer;
    QTimer *enemychangedir_timer;
    QTimer *enemymove_timer;



    //{left,down,right,up}
};


class Basic :public Enemy
{
    Q_OBJECT
public:
    Basic();

public slots:
    void move();
    void straightmove();
};

class Fast: public Enemy
{
    Q_OBJECT
public:
    Fast();
public slots:
    void move();
};

class Power: public Enemy
{
    Q_OBJECT
public:
    Power();
public slots:
    void move();
};

class Armor: public Enemy
{
    Q_OBJECT
public:
    Armor();
public slots:
    void move();
};

#endif // ENEMY_H

