#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QKeyEvent>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public slots:
    virtual void move()=0;

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
signals:
    void bulletHitsEnemy();

private:
    Qt::Key direction;
};

class Enemy_Bullet : public Bullet
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation )
public:
    Enemy_Bullet(int dir);
    //~Bullet();

    qreal rotation() const;
    void setRotation(qreal newRotation);

public slots:
    //void spawn();
    void move();

signals:
    void bulletHitsPlayer();
         //void bullethitsEnemy(Bullet *bullet , Enemy *enemy);

private:
    int dir;
    QTimer *timer;
    qreal m_rotation;
};

#endif // BULLET_H
