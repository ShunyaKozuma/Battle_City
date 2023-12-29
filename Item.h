#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QTimer>
#include <QObject>
#include <QPropertyAnimation>
#include <QGraphicsPixmapItem>
#include "Enemy.h"
#include "Bullet.h"
#include "Obstruction.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <stdlib.h>
#include <QtGlobal>
#include <ctime>


class Item : public QObject , public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    //explicit Item(QObject *parent = nullptr);

signals:

};

class Grenade : public Item
{
    Q_OBJECT
public:
    Grenade();
};

class Helmet : public Item
{
    Q_OBJECT
public:
    Helmet();
};

class Shovel : public Item
{
    Q_OBJECT
public:
    Shovel();
};

class Star : public Item
{
    Q_OBJECT
public:
    Star();
};

class Tank : public Item
{
    Q_OBJECT
public:
    Tank();
};

// Timer may not be suitable because the sysytem
class SpecialTimer : public Item
{
    Q_OBJECT
public:
    SpecialTimer();
};
#endif // ITEM_H
