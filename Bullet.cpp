#include "bullet.h"
#include "Brick.h"
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsRectItem>
#include <QRect>

Bullet::Bullet(Qt::Key keyDirection)
{
    direction = keyDirection;
    //setPixmap(QPixmap(":/images/bullet_up.png"));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Bullet::move);
    timer->start(50); // fires every 50ms
}

Bullet::~Bullet()
{
    delete timer;
}

void Bullet::move()
{
    int step = 10; // Set the step size for bullet movement

    // Update the bullet's position based on the direction

    if (direction == Qt::Key_Up){
        setPixmap(QPixmap(":/images/bullet_up.png").scaled(10,10));
        setPos(x(), y() - step);
    } else if (direction == Qt::Key_Down){
        setPixmap(QPixmap(":/images/bullet_down.png").scaled(10,10));
        setPos(x(), y() + step);
    } else if (direction == Qt::Key_Left){
        setPixmap(QPixmap(":/images/bullet_left.png").scaled(10,10));
        setPos(x() - step, y());
    } else if (direction == Qt::Key_Right){
        setPixmap(QPixmap(":/images/bullet_right.png").scaled(10,10));
        setPos(x() + step, y());
    } else {
        setPos(x(), y() - step);
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i < n; i++){
        if(typeid(*colliding_items[i]) == typeid(Brick)){

            scene()->removeItem(colliding_items[i]);
            //delete bullt after 0 s, this releses memories so must write
            QTimer::singleShot(0, this, [this]() {
                scene()->removeItem(this);
                delete this;
            });
            //delete this; an error occures when state this code
        }
    }

    if (y() + boundingRect().height() < 0) {
        // Remove the bullet from the scene first
        scene()->removeItem(this);
        delete this;
    }
    //delete this;
}
