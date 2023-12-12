#ifndef STEEL_H
#define STEEL_H

#include "Obstruction.h"
#include <QObject>
#include <QGraphicsPixmapItem>


class Steel : public Obstruction
{
    Q_OBJECT
public:
    Steel();
    Steel(int x, int y);
    int getType();  //return which type of block
    //qreal x() const;

signals:

private:
    QGraphicsPixmapItem *steel;

};

#endif // STEEL_H
