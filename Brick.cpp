#include "Brick.h"
#include "Player.h"
#include <QGraphicsScene>

Brick::Brick()
{
    setPixmap(QPixmap(":/images/brick.png"));
}

Brick::Brick(int x, int y)
{
    setPixmap(QPixmap(":/images/brick.png"));
    setPos(x, y);

    /*
    QTimer *bricktimer = new QTimer(this);
    connect(bricktimer, &QTimer::timeout, this, &Brick::brickHitPlayer);
    playertimer->start(50);
    */
}

int Brick::getType()
{
    return 1;
}

/* the part which a brick is shot by player
            QGraphicsItem *itemToDelete = colliding_items[i];
            scene()->removeItem(itemToDelete);
            delete itemToDelete;*/
