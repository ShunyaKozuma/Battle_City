#ifndef ENEMY_H
#define ENEMY_H


#include <QTimer>
#include <QObject>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>

//the step of enemy tank
#define STEP 10

class Enemy :public QObject ,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation )

public:
    qreal rotation() const;
    void setRotation(qreal newRotation);
    void stopEnemyTank();
    void turn();


public slots:
    virtual void move()=0;
    bool enemy_collisionWithObstacle(const QPointF &nextPos, const QPointF &pos);
    void LosePLayer();


signals:
    void enemyHitsTheGrounds(Enemy *enemy);
    void TellSceneLosePlayer();

protected:
    void shootbullet(int i, int tank_type);
    QTimer *timer;
    int countStep;
    int dir;
    const QList<QPointF> directionList = {QPointF(-STEP, 0), QPointF(0, STEP), QPointF(STEP, 0), QPointF(0, -STEP)};
private:
    qreal m_rotation;
    //{left,down,right,up}
};


class Basic :public Enemy
{
    Q_OBJECT
public:
    Basic();
public slots:
    void move();
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

class Flashing :public Enemy
{
    Q_OBJECT
public:
    Flashing();
public slots:
    void move();
    void flash();
private:
    bool isFirstAppearance{true};
};

#endif // ENEMY_H

