#ifndef POWERUP_H
#define POWERUP_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsScene>
#include "Player.h"

class PowerUp: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    enum PowerUpType {
        Grenade,
        Helmet,
        Shovel,
        Star,
        Tank,
        Timer
    };

    PowerUp(PowerUpType type);
    void activate();

signals:
    void collected(PowerUpType type);

private:
    PowerUpType type;
    //QPixmap pixmapForType(int type);  // Function to get the appropriate pixmap for each type

};

#endif // POWERUP_H
