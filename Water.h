#ifndef WATER_H
#define WATER_H

#include "Obstruction.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Water : public Obstruction
{
    Q_OBJECT
public:
    Water();
    int getType();  //return which type of block
    //qreal x() const;

signals:

private:
    QGraphicsPixmapItem *water;

};

#endif // WATER_H
