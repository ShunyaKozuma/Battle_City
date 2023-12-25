#include "Player.h"
#include "Obstruction.h".h"
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

