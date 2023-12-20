#include "Enemy.h"
#include "Bullet.h"
#include "Brick.h"
#include "Steel.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <stdlib.h>
#include <QtGlobal>
#include <ctime>
#include<QDebug>
#include"Scene.h"
Basic::Basic()
{
    setPixmap(QPixmap(":/images/Fast_Tank.png").scaled(40,40));
    srand(time(NULL));
    dir = 1; //初始位置

    //
    shoot_timer=new QTimer();
    enemymove_timer=new QTimer();
    enemychangedir_timer=new QTimer();
    connect(shoot_timer, &QTimer::timeout, this, &Enemy::needshootbullet );
    connect(enemymove_timer, &QTimer::timeout,this, &Enemy::straightmove);
    connect(enemychangedir_timer, &QTimer::timeout,this, &Enemy::move );
    shoot_timer->start(300);//要設定如果場內沒有bullet才能射擊
    enemymove_timer->start(50);
    enemychangedir_timer->start(1000);
    //
    //timer = new QTimer();
    //connect(timer, &QTimer::timeout, this, &Enemy::move );
    //timer->start(100);


//have to set another timer to control a frequency of the enemy bullets
    setZValue(1);
}

void Basic::straightmove(){
    QPointF enemy_nextPos = pos() + directionList[dir];
    // 如果碰到視窗邊緣則將位置設成視窗邊緣
    if(!enemy_collisionWithObstacle(enemy_nextPos,pos())){//如果沒有碰到障礙物
        enemy_nextPos.setX(qBound(0.0, enemy_nextPos.x(), 600.0));
        enemy_nextPos.setY(qBound(0.0, enemy_nextPos.y(), 600.0));
        //qDebug()<<"enemy_nextPos."<<enemy_nextPos;


        this->setPos(enemy_nextPos);}
    //qDebug()<<x()<<y();

}
void Basic::move()
{


    dir = rand() % 4;
    //qDebug()<<dir;

    //int dir = rand() % 4;
    //detect which direction is the best.
    /*
    for(int i=0; i<4; i++){
        Enemy_nextPos = pos() + directionList[i];
    }
    */
    //dir=5;
    int direction = dir;
    //QPointF enemy_nextPos = pos() + directionList[direction];
    //if(!enemy_collisionWithObstacle(enemy_nextPos,pos())){
    if(1){//如果碰到牆壁則在牆壁位置發呆，如果碰到磚牆禁止移動
        switch (direction) {
        case 0:
            setRotation(270);
            //Enemy_nextPos = QPointF(x(),y() + 10);
            qDebug()<<"270";
            break;
        case 1:
            setRotation(180);
            qDebug()<<"180";
            break;
        case 2:
            setRotation(90);
            qDebug()<<"90";
            break;
        default:
            setRotation(0);
            qDebug()<<"0";
            break;
        }
        //setPos(enemy_nextPos);
        //shootbullet(direction);
    }else{
        //dir = rand()%4;
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
    //timer = new QTimer();
    //connect(timer, &QTimer::timeout, this, &Enemy::move );
    //timer->start(100);
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
    qDebug()<<dir;

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
    //scene()->Liv
    //QGraphicsScene *currentScene = scene();
    //connect(bullet, &Enemy_Bullet::loselive, scene ,static_cast<void (Scene::*)()>(&Scene::LiveMinus));
    //scene()->connect(bullet, &Enemy_Bullet::loselive, this , &Scene::LiveMinus);

        // 设置子弹初始位置为敌人位置


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

void Enemy::needshootbullet()
{
    int ExistBullet=0;
    foreach (QGraphicsItem *item,scene()->items()) {
        if(typeid(*item) == typeid(Enemy_Bullet)){
            ExistBullet=1;
            break;
        }}
    if( ExistBullet==0){
        shootbullet(dir);}


}


