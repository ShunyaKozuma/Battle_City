#include "Item.h"

Grenade::Grenade()
{
    setPixmap(QPixmap(":/images/Grenade_Item.png").scaled(45,45));
}

Helmet::Helmet()
{
    setPixmap(QPixmap(":/images/Helmet_Item.png").scaled(45,45));
}

Shovel::Shovel()
{
    setPixmap(QPixmap(":/images/Shovel_Item.png").scaled(45,45));
}

Star::Star()
{
    setPixmap(QPixmap(":/images/Star_Item.png").scaled(45,45));
}

Tank::Tank()
{
    setPixmap(QPixmap(":/images/Tank_Item.png").scaled(45,45));
}

SpecialTimer::SpecialTimer()
{
    setPixmap(QPixmap(":/images/SpecialTimer_Item.png").scaled(45,45));
}
