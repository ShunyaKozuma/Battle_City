#ifndef ENEMYHEALTH_H
#define ENEMYHEALTH_H

#include <QObject>
#include <QGraphicsPixmapItem>

class EnemyHealth : public QObject ,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    //explicit EnemyHealth(QObject *parent = nullptr);
    EnemyHealth();
    void decrease();

private:
    int Enemyhealth;

signals:

};

#endif // ENEMYHEALTH_H
