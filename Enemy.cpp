#include "Enemy.h"
#include "Bullet.h"
#include "Obstruction.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <stdlib.h>
#include <QtGlobal>
#include <ctime>

void Enemy::stopEnemyTank(){
    if (timer->isActive()) {
        timer->stop();
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

void Enemy::shootbullet(int direction,int tank_type)
{
    //Qt::Key direction = directionList[dir];
    Enemy_Bullet *bullet = new Enemy_Bullet(direction,tank_type,helmet); // 创建子弹对象
    connect(bullet,Bullet::LosePlayerLife,this,Enemy::LosePLayer);
    //connect(bullet,Bullet::pauseEneBullet,this,Bullet::stopMoving);


    switch (direction) {
    case 0:
        bullet->setRotation(270);
        bullet->setPos(x()+16, y()+3);
        break;
    case 1:
        bullet->setRotation(180);
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

void Enemy::sethelmet()
{
    helmet=true;
}

void Enemy::unsethelmet()
{
    helmet=false;
}

int Enemy::decreaseArmorHealth()
{
    armor_health--;
    return armor_health;
}

bool Enemy::enemy_collisionWithObstacle(const QPointF &nextPos, const QPointF &pos)
{
    setPos(nextPos);
    QList<QGraphicsItem *> collidin_items = collidingItems();
    setPos(pos);
    for (QGraphicsItem *item : collidin_items) {
        if (typeid(*item) == typeid(Brick) || typeid(*item) == typeid(Steel) ||typeid(*item) == typeid(Water)) {
            return true;
        }
    }
    return false;
}

void Enemy::LosePLayer()//用來刪掉player的
{
    emit TellSceneLosePlayer();
}

Basic::Basic()
{
    setPixmap(QPixmap(":/images/basic.png").scaled(45,45));
    srand(time(NULL));
    dir = 1;
    helmet=false;
    turn();
    score=100;
    countStep=0;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::move );
    timer->start(100);
    setZValue(1);
}

void Basic::move()
{
    countStep++;
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
        if(countStep==15)
        {
            shootbullet(dir,1);
            countStep=0;
        }

    }else{
        dir = rand()%4;
        turn();
    }
}

Fast::Fast()
{
    setPixmap(QPixmap(":/images/Fast_Tank.png").scaled(45,45));
    srand(time(NULL));
    helmet=false;
    dir = 1;
    turn();
    score=200;
    countStep=0;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::move );
    timer->start(33);
    setZValue(1);
}

void Fast::move()
{
    countStep++;

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
            shootbullet(dir,2);
            countStep=0;
        }

    }else{
        dir = rand()%4;
        turn();
    }
}

Power::Power()
{
    setPixmap(QPixmap(":/images/Power_Tank.png").scaled(45,45));
    srand(time(NULL));
    helmet=false;
    dir = 1;
    turn();
    score=300;
    countStep=0;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::move );
    timer->start(50);
    setZValue(1);
}

void Power::move()
{
    countStep++;
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
            shootbullet(dir,3);
            countStep=0;
        }

    }else{
        dir = rand()%4;
        turn();
    }
}

Armor::Armor()
{
    setPixmap(QPixmap(":/images/Armor_Tank.png").scaled(45,45));
    srand(time(NULL));
    helmet=false;
    dir = 1;
    turn();
    score=400;
    countStep=0;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::move );
    timer->start(50);
    setZValue(1);
}

void Armor::move()
{
    countStep++;
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
            shootbullet(dir,4);
            countStep=0;
        }

    }else{
        dir = rand()%4;
        turn();
    }
}

Flashing::Flashing()
{
    setPixmap(QPixmap(":/images/Fast_Tank.png").scaled(45,45));
    srand(time(NULL));
    helmet=false;
    dir = 1;
    turn();
    score=100;
    countStep=0;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Enemy::move);
    timer->start(100);

    QTimer* flashingTimer = new QTimer(this);
    connect(flashingTimer, &QTimer::timeout, this, &Flashing::flash);
    flashingTimer->start(100);
}

void Flashing::move()
{
    countStep++;
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
            shootbullet(dir,1);
            countStep=0;
        }

    }else{
        dir = rand()%4;
        turn();
    }
}

void Flashing::flash()
{
    if (isFirstAppearance) {
        setPixmap(QPixmap(":/images/Fast_Tank.png").scaled(45,45));
    } else {
        setPixmap(QPixmap(":/images/Flashing_Tank.png").scaled(45,45));
    }

    isFirstAppearance = !isFirstAppearance;
}

void Enemy::defreeze()
{
    timer->start();
    //foreach(QGraphicsItem *item, scene()->items()) {
    //    if (Enemy_Bullet *enebullet = dynamic_cast<Enemy_Bullet*>(item))  {
    // 执行 freezeInPlace 方法
    //        enebullet->defreeze();
    //    }
    //}

}

int Enemy::getscore()
{
    return score;
}
/*
void Enemy::freezeInPlace()
{

    timer->stop();

    foreach(QGraphicsItem *item, this->scene()->items()) {
        if (Enemy_Bullet *enebullet = dynamic_cast<Enemy_Bullet*>(item))  {
        // 执行 freezeInPlace 方法

            enebullet->freezeInPlace();

            }
        }


}
*/
