#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QKeyEvent>

class Player : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Player();

private:
    //QTimer *timer;
    Qt::Key direction;
    bool frozen;
/*
signals:
    void playerHitWall();
*/
};

#endif // PLAYER_H
