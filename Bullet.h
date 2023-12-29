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

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    void handleCollision(QGraphicsItem* item);

public slots:
    virtual void move()=0;

signals:
    void bulletHitEnemy(Bullet *bullet, Enemy *enemy);
    void LosePlayerLife();
    void bulletHitFlashing();

protected:
    QTimer *timer;
};

class Player_Bullet : public Bullet
{
    Q_OBJECT
public:
    Player_Bullet(Qt::Key keyDirection);
    ~Player_Bullet();

public slots:
    void move();

private:
    Qt::Key direction;
};

class Enemy_Bullet : public Bullet
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation )
public:
    Enemy_Bullet(int dir,int tank_type);
    //~Bullet();

    qreal rotation() const;
    void setRotation(qreal newRotation);

public slots:
    //void spawn();
    void move();

signals:
         //void bullethitsEnemy(Bullet *bullet , Enemy *enemy);

private:
    int dir;
    int tank_type;
    QTimer *timer;
    qreal m_rotation;
};

#endif // BULLET_H
