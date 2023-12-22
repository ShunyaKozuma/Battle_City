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
};

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

class Trees : public Obstruction
{
    Q_OBJECT
public:
    Trees();
    Trees(int x, int y);
    int getType();  //return which type of block
    //qreal x() const;

signals:

private:
    QGraphicsPixmapItem *trees;

};

class Water : public Obstruction
{
    Q_OBJECT
public:
    Water();
    Water(int x, int y);
    int getType();  //return which type of block
    //qreal x() const;

signals:

private:
    QGraphicsPixmapItem *water;

};

class Ice : public Obstruction
{
    Q_OBJECT
public:
    Ice();
    Ice(int x, int y);
    int getType();  //return which type of block
    //qreal x() const;

signals:

private:
    QGraphicsPixmapItem *ice;

};
#endif // OBSTRUCTION_H
