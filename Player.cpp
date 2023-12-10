#include "Player.h"
#include "Brick.h"
#include "Bullet.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QPointF>

Player::Player()
{
    setPixmap(QPixmap(":/images/player1_up.png").scaled(40,40));
    setZValue(1);
}

/*
void Player::move()
{

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i < n; i++){
        if(typeid(*colliding_items[i]) == typeid(Brick)){

            freeze();
            QTimer::singleShot(100, this, [this](){ unfreeze();});
        }
    }
}

//brick.cppにcollisionをかいて、playerに行くようにする
*/
