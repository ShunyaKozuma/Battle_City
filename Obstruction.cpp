#include "Obstruction.h"
#include "Player.h"
#include <QGraphicsScene>

Obstruction::Obstruction()
{

}

Obstruction::~Obstruction()
{

}

int Obstruction::getType()
{
    return 0;
}

Brick::Brick()
{
    setPixmap(QPixmap(":/images/brick.png"));
}

Brick::Brick(int x, int y)
{
    setPixmap(QPixmap(":/images/brick.png"));
    setPos(x, y);
}

int Brick::getType()
{
    return 1;
}

Steel::Steel()
{
    setPixmap(QPixmap(":/images/steel.png"));
}

Steel::Steel(int x, int y)
{
    setPixmap(QPixmap(":/images/steel.png"));
    setPos(x,y);
}

int Steel::getType()
{
    return 2;
}

Trees::Trees()
{
    setPixmap(QPixmap(":/images/trees.png").scaled(25,25));
    setZValue(2);
}

Trees::Trees(int x, int y)
{
    setPixmap(QPixmap(":/images/trees.png").scaled(25,25));
    setZValue(2);
    setPos(x,y);

}

int Trees::getType()
{
    return 3;
}


Water::Water()
{
    setPixmap(QPixmap(":/images/water.png").scaled(25,25));
}

Water::Water(int x, int y)
{
    setPixmap(QPixmap(":/images/water.png").scaled(25,25));
    setPos(x,y);

}

int Water::getType()
{
    return 4;
}

Ice::Ice()
{
    setPixmap(QPixmap(":/images/ice.png").scaled(25,25));
}

Ice::Ice(int x, int y){

    setPixmap(QPixmap(":/images/ice.png").scaled(25,25));
    setPos(x,y);
}

int Ice::getType()
{
    return 5;
}

