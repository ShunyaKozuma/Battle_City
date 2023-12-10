#ifndef BRICK_H
#define BRICK_H

#include "Obstruction.h"
#include <QObject>
#include <QGraphicsItemGroup>

class Brick : public Obstruction
{
    Q_OBJECT
public:
    Brick();
    Brick(int x, int y);
    int getType();  //return which type of block
    //qreal x() const;

signals:

private:
    QGraphicsPixmapItem *brick;
    //QTimer *blicktimer;

};

#endif // BRICK_H
