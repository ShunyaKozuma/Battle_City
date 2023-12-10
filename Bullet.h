#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QKeyEvent>

class Bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(Qt::Key keyDirection);
    ~Bullet();

public slots:
    void move();

private:
    QTimer *timer;
    Qt::Key direction;
};

#endif // BULLET_H
