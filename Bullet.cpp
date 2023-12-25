#include "bullet.h"
#include <Item.h>
// handle all bullet collison, set the case of steel, water, trees and Ice
void Bullet::handleCollision(QGraphicsItem *item){
    //qDebug() << typeid(*item).name();

    if(typeid(*item) == typeid(Brick)){
        //directly delete when item is a brick
        scene()->removeItem(item);
        delete item;
    }else if(Enemy *enemy = dynamic_cast<Enemy*>(item)){
        emit bulletHitEnemy(this, enemy);
        scene()->removeItem(item);
        delete item;

    }
    // delete bullet after 0 seconds, this releases memory
    QTimer::singleShot(0, this, [this, item]() {
        scene()->removeItem(this);
        delete this;
    });
}


Player_Bullet::Player_Bullet(Qt::Key keyDirection)
{
    direction = keyDirection;
    //setPixmap(QPixmap(":/images/bullet_up.png"));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50); // fires every 50ms
}

Player_Bullet::~Player_Bullet()
{
    delete timer;
}

void Player_Bullet::move()
{
    int step = 10; // Set the step size for bullet movement

    // Update the bullet's position based on the direction
    // Changed the bullet's size from 10,10 to 10,20 (12/22)

    if (direction == Qt::Key_Up){
        setPixmap(QPixmap(":/images/bullet_up.png").scaled(10,20));
        setPos(x(), y() - step);
    } else if (direction == Qt::Key_Down){
        setPixmap(QPixmap(":/images/bullet_down.png").scaled(10,20));
        setPos(x(), y() + step);
    } else if (direction == Qt::Key_Left){
        setPixmap(QPixmap(":/images/bullet_left.png").scaled(10,20));
        setPos(x() - step, y());
    } else if (direction == Qt::Key_Right){
        setPixmap(QPixmap(":/images/bullet_right.png").scaled(10,20));
        setPos(x() + step, y());
    } else {
        setPos(x(), y() - step);
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i < n; i++){
        // when the bullet shoot, the colliding_items include Player and others. So just not ref Player.
        if(typeid(*colliding_items[i]) != typeid(Player) and typeid(*colliding_items[i]) != typeid(Water)and typeid(*colliding_items[i]) != typeid(Trees)and typeid(*colliding_items[i]) != typeid(Ice)){
            //scene()->removeItem(colliding_items[i]);
            //delete colliding_items[i];
            handleCollision(colliding_items[i]);
            }
        //1225新增，己方子彈打到老鷹結束遊戲
        if(typeid(*colliding_items[i]) == typeid(Eagle)){
                emit LosePlayerLife();}

    }

    if (x() + boundingRect().width() > 650 || y() + boundingRect().height() < 0) {
        // Remove the bullet from the scene first
        scene()->removeItem(this);
        delete this;
    }
    //delete this;
}


Enemy_Bullet::Enemy_Bullet(int direction):dir(direction)
{
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(100);
    setZValue(0);
}

void Enemy_Bullet::move()
{
    setPixmap(QPixmap(":/images/bullet_up.png").scaled(10,20));
    switch (dir) {
    case 0:
        setRotation(270);
        setPos(x() - 10 , y());
        break;
    case 1:
        setRotation(180);
        setPos(x() , y() + 10);
        break;
    case 2:
        setRotation(90);
        setPos(x() + 10 , y());
        break;
    default:
        setRotation(270);
        setPos(x() , y() - 10);
        break;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i < n; i++){
        if (typeid(*colliding_items[i]) != typeid(Basic)and typeid(*colliding_items[i]) != typeid(Water)and typeid(*colliding_items[i]) != typeid(Trees)and typeid(*colliding_items[i]) != typeid(Ice)) {
        //if (Enemy *enemy = dynamic_cast<Enemy*>(colliding_items[i])) {
            //qDebug() << typeid(*colliding_items[i]).name();
            handleCollision(colliding_items[i]);
        }
        //1225新增，呼叫enemy，己方子彈打到老鷹與player結束遊戲
        if(typeid(*colliding_items[i]) == typeid(Player)||typeid(*colliding_items[i]) == typeid(Eagle)){
            //scene()->removeItem(this);
            //delete this;
            emit LosePlayerLife();}

        //write other enemy tank version
    }

    if (x() + boundingRect().width() > 650 || y() + boundingRect().height() < 0) {
        // Remove the bullet from the scene first
        scene()->removeItem(this);
        delete this;
    }
}

qreal Enemy_Bullet::rotation() const
{
    return m_rotation;
}

void Enemy_Bullet::setRotation(qreal newRotation)
{
    m_rotation = newRotation;
    QPointF c =boundingRect().center();
    QTransform t;
    t.translate(c.x(),c.y());
    t.rotate(newRotation);
    t.translate(-c.x(),-c.y());
    setTransform(t);
}
