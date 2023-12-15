#include "Enemy.h"
#include "Bullet.h"
#include "Brick.h"
#include "Steel.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <stdlib.h>
#include <QtGlobal>
#include <ctime>

Basic::Basic()
{
    setPixmap(QPixmap(":/images/Fast_Tank.png").scaled(40,40));
    srand(time(NULL));
    dir = 1;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::move );
    timer->start(100);
//have to set another timer to control a frequency of the enemy bullets
    setZValue(1);
}

void Basic::move()
{
    //int dir = rand() % 4;

    //detect which direction is the best.
    /*
    for(int i=0; i<4; i++){
        Enemy_nextPos = pos() + directionList[i];
    }
    */
    //dir=5;
    int direction = dir;
    QPointF enemy_nextPos = pos() + directionList[direction];
    if(!enemy_collisionWithObstacle(enemy_nextPos,pos())){
        switch (direction) {
        case 0:
            setRotation(270);
            //Enemy_nextPos = QPointF(x(),y() + 10);
            break;
        case 1:
            setRotation(180);
            break;
        case 2:
            setRotation(90);
            break;
        default:
            setRotation(0);
            break;
        }
        setPos(enemy_nextPos);
        shootbullet(direction);
    }else{
        dir = rand()%4;
    }
    //shootbullet(direction);
}



Fast::Fast()
{
    setPixmap(QPixmap(":/images/Fast_Tank.png"));
    srand(time(NULL));
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::move );
    timer->start(100);
}

void Fast::move()
{
    int dir = rand() % 4;
    switch (dir) {
    case 0:
        setRotation(90);
        setPos(x() , y() + 5);
        break;
    case 1:
        setRotation(0);
        setPos(x() , y() - 5);
        break;
    case 2:
        setRotation(180);
        setPos(x() + 5 , y());
        break;
    default:
        setRotation(270);
        setPos(x() - 5 , y());
        break;
    }
    shootbullet(dir);
}

Power::Power()
{
    setPixmap(QPixmap(":/images/Power_Tank.png"));
    srand(time(NULL));
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::move );
    timer->start(100);
}

void Power::move()
{
    int dir = rand() % 4;

    switch (dir) {
    case 0:
        setRotation(90);
        setPos(x() , y() + 5);
        break;
    case 1:
        setRotation(0);
        setPos(x() , y() - 5);
        break;
    case 2:
        setRotation(180);
        setPos(x() + 5 , y());
        break;
    default:
        setRotation(270);
        setPos(x() - 5 , y());
        break;
    }
    shootbullet(dir);
}

Armor::Armor()
{
    setPixmap(QPixmap(":/images/Armor_Tank.png"));
    srand(time(NULL));
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::move );
    timer->start(100);
}

void Armor::move()
{
    int dir = rand() % 4;

    switch (dir) {
    case 0:
        setRotation(90);
        setPos(x() , y() + 5);
        break;
    case 1:
        setRotation(0);
        setPos(x() , y() - 5);
        break;
    case 2:
        setRotation(180);
        setPos(x() + 5 , y());
        break;
    default:
        setRotation(270);
        setPos(x() - 5 , y());
        break;
    }
    shootbullet(dir);
}

qreal Enemy::rotation() const
{
    return m_rotation;
}

void Enemy::setRotation(qreal newRotation)
{
    m_rotation = newRotation;
    QPointF c =boundingRect().center();
    QTransform t;
    t.translate(c.x(),c.y());
    t.rotate(newRotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}

void Enemy::shootbullet(int direction)
{
    //Qt::Key direction = directionList[dir];
    Enemy_Bullet *bullet = new Enemy_Bullet(direction); // 创建子弹对象
        // 设置子弹初始位置为敌人位置

    switch (direction) {
    case 0:
        bullet->setRotation(270);
        qDebug()<<pos();
        bullet->setPos(x()+16, y()+3);
        break;
    case 1:
        bullet->setRotation(180);
        qDebug()<<pos();
        bullet->setPos(x()+16, y()+3);
        break;
    case 2:
        bullet->setRotation(90);
        bullet->setPos(x()+16, y()+3);
        break;
    default:
        bullet->setRotation(0);
        bullet->setPos(x()+16, y()-3);
        break;
    }

    scene()->addItem(bullet);

}

bool Enemy::enemy_collisionWithObstacle(const QPointF &nextPos, const QPointF &pos)
{
    setPos(nextPos);
    QList<QGraphicsItem *> collidin_items = collidingItems();
    setPos(pos);
    for (QGraphicsItem *item : collidin_items) {
        if (typeid(*item) == typeid(Brick) || typeid(*item) == typeid(Steel) ) {
            return true;
        }
    }
    return false;
}
