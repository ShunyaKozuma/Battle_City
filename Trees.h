#ifndef TREES_H
#define TREES_H

#include "Obstruction.h"
#include <QObject>
#include <QGraphicsPixmapItem>

class Trees : public Obstruction
{
    Q_OBJECT
public:
    Trees();
    int getType();  //return which type of block
    //qreal x() const;

signals:

private:
    QGraphicsPixmapItem *trees;

};

#endif // TREES_H
