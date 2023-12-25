#include "Enemy.h"
#include "Bullet.h"
#include "Obstruction.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <stdlib.h>
#include <QtGlobal>
#include <ctime>

Basic::Basic()
{
    setPixmap(QPixmap(":/images/Fast_Tank.png").scaled(45,45));
    srand(time(NULL));
    dir = 1;
    turn();
    countStep=0;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::move );
    timer->start(100);
    setZValue(1);
}

void Basic::move()
{
    countStep++;
    qDebug()<<"Enter Move";
    QPointF enemy_nextPos = pos() + directionList[dir];
    if(enemy_nextPos.x()<0 || enemy_nextPos.x()>600 || enemy_nextPos.y()<0 || enemy_nextPos.y()>650)
    {
        enemy_nextPos.setX(qBound(0.0, enemy_nextPos.x(), 600.0));
        enemy_nextPos.setY(qBound(0.0, enemy_nextPos.y(), 600.0));
        dir = rand()%4;
        turn();
    }
    if(!enemy_collisionWithObstacle(enemy_nextPos,pos())){
        int random_factor = rand()% 100;
        if(random_factor>=87)
        {
            dir = rand()%4;
            turn();
        }
        setPos(enemy_nextPos);
        if(countStep==25)
        {
            shootbullet(dir);
            countStep=0;
        }

    }else{
        dir = rand()%4;
        turn();
    }
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
    connect(bullet,Bullet::LosePlayerLife,this,Enemy::LosePLayer);
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

void Enemy::turn()
{
    switch (dir) {
    case 0:
        setRotation(270);
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
}

bool Enemy::enemy_collisionWithObstacle(const QPointF &nextPos, const QPointF &pos)
{
    setPos(nextPos);
    QList<QGraphicsItem *> collidin_items = collidingItems();
    setPos(pos);
    for (QGraphicsItem *item : collidin_items) {
        if (typeid(*item) == typeid(Brick) || typeid(*item) == typeid(Steel) ||typeid(*item) == typeid(Water)) {
            qDebug()<<"crash";
            return true;
        }
    }
    qDebug()<<"no crash";
    return false;
}

void Enemy::LosePLayer()//用來刪掉player的
{
    emit TellSceneLosePlayer();
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
