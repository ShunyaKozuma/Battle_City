#include "Steel.h"

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
