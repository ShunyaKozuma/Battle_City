#ifndef OBSTRUCTION_H
#define OBSTRUCTION_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>

class Obstruction : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Obstruction();
    virtual ~Obstruction();

    virtual int getType();  //return which type of block
    //qreal x() const;

signals:

};

#endif // OBSTRUCTION_H
