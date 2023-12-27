#include "PowerUp.h"
#include <QTimer>


PowerUp::PowerUp(PowerUpType type) : QObject(), QGraphicsPixmapItem()
{
    this->type = type;

    setPixmap(pixmapForType(type));
}

void PowerUp::activate()
{
    // Implement the specific effects of each power-up type
    switch (type) {
    case Grenade:
        // Destroy all enemies on the screen
        // ...
        break;
    case Helmet:
        // Give temporary force field
        // ...
        break;
        // Implement other power-up effects
    }
}

QPixmap PowerUp::pixmapForType(PowerUpType type)
{
    // Implement logic to return the appropriate pixmap for each power-up type
    switch (type) {
    case Grenade:
        return QPixmap(":/images/Grenade_Item.png".scaled(45,45));
    case Helmet:
        return QPixmap(":/images/Helmet_Item.png".scaled(45,45));
    case Shovel:
        return QPixmap(":/images/Shovel_Item.png".scaled(45,45));
    case Star:
        return QPixmap(":/images/Star_Item.png".scaled(45,45));
    case Tank:
        return QPixmap(":/images/Tank_Item.png".scaled(45,45));
    case Timer:
        return QPixmap(":/images/Timer_Item.png".scaled(45,45));
}

