#ifndef ICE_H
#define ICE_H

#include "Obstruction.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Ice : public Obstruction
{
    Q_OBJECT
public:
    Ice();
    int getType();  //return which type of block
    //qreal x() const;

signals:

private:
    QGraphicsPixmapItem *ice;

};

#endif // ICE_H
