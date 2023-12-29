#include "PowerUp.h"
#include <QTimer>

// state this when the flashing enemy is defeated
PowerUp::PowerUp(PowerUpType type) : QObject(), QGraphicsPixmapItem()
{
    this->type = type;
    //setPixmap(pixmapForType(type)); not working
    switch (type) {
    case Grenade:
        setPixmap(QPixmap(":/images/Grenade_Item.png").scaled(40,40));
        break;
    case Helmet:
        setPixmap(QPixmap(":/images/Helmet_Item.png").scaled(45,45));
        break;
    case Shovel:
        setPixmap(QPixmap(":/images/Shovel_Item.png").scaled(45,45));
        break;
    case Star:
        setPixmap(QPixmap(":/images/Star_Item.png").scaled(45,45));
        break;
    case Tank:
        setPixmap(QPixmap(":/images/Tank_Item.png").scaled(45,45));
        break;
    case Timer:
        setPixmap(QPixmap(":/images/SpecialTimer_Item.png").scaled(45,45));
        break;
    // Add cases for other power-up types
        //return QPixmap(); // Return an empty pixmap for unknown types
    }

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &PowerUp::activate);
    /*
    connect(timer, &QTimer::timeout, [this]() {
        emit collected(type); // Signal that the power-up has been collected
        delete this; // Delete the power-up object
    });
*/
    timer->start(100);
}

void PowerUp::activate()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i=0, n = colliding_items.size(); i < n; i++){
        if (typeid(*colliding_items[i]) == typeid(Player)) {
            emit collected(type);
            scene()->removeItem(this);
            QTimer::singleShot(0, this, [this]() {
                delete this;
            });
        }
    }
}

/*
QPixmap PowerUp::pixmapForType(PowerUpType type)
{
    // Implement logic to return the appropriate pixmap for each power-up type
    switch (type) {
    case Grenade:
        return QPixmap(":/images/Grenade_Item.png".scaled(45,45));
    case Helmet:
        return QPixmap(":/images/Helmet_Itw.png".scaled(45,45));
    // Add cases for other power-up types
    default:
        return QPixmap(); // Return an empty pixmap for unknown types
    }
}
*/

