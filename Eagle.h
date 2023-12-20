#ifndef EAGLE_H
#define EAGLE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>

class Eagle : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Eagle();

private:

};

#endif // EAGLE_H
