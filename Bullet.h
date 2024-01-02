#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QList>
#include <QRect>
#include "Player.h"
#include "Obstruction.h"
#include "Enemy.h"
#include "Enemyhealth.h"
#include "Eagle.h"
#include "PowerUp.h"

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    void handleCollision(QGraphicsItem* item);
    void freezeInPlace();
    void defreeze();

public slots:
    virtual void move()=0;

signals:
    void bulletHitEnemy(Bullet *bullet, Enemy *enemy);
    void LosePlayerLife();
    void bulletHitFlashing();
    void playerbulletgone();
    void addscroe(int);

protected:
    QTimer *timer;
};

class Player_Bullet : public Bullet
{
    Q_OBJECT
public:
    Player_Bullet(Qt::Key keyDirection,int speedbuff,bool powerbuff);
    ~Player_Bullet();
    bool getbulletpowerbuff();
    int setpowerbuff_breakbrick_max();
    int getpowerbuff_breakbrick_max();

signals:


public slots:
    void move();

private:
    Qt::Key direction;
    int bulletspeedbuff;
    bool bulletpowerbuff;
    int powerbuff_breakbrick_max=0;
};

class Enemy_Bullet : public Bullet
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation )
public:
    Enemy_Bullet(int dir,int tank_type,bool helmet);
    //~Bullet();

    qreal rotation() const;
    void setRotation(qreal newRotation);
    bool checkHelmet();

public slots:
    //void spawn();
    void move();

signals:
         //void bullethitsEnemy(Bullet *bullet , Enemy *enemy);

private:
    int dir;
    int tank_type;
    bool helmet;
    QTimer *timer;
    qreal m_rotation;
};

#endif // BULLET_H
