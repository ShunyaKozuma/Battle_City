#include "Scene.h"

#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QList>
// file operation
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QResource>
#include <QDebug>

Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{

    QString resourcePath = ":/word/obstacle.txt";
    QResource::registerResource("res.qrc");
    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file: " << file.errorString();
        //return 1;
    }

    // 创建QTextStream对象，并将其与文件关联
    QTextStream in(&file);

    // 读取文件内容
    int background_num[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; ++i)
    {
        QString line = in.readLine();
        // 将数字转换为整数并存储在数组中
        for (int j = 0; j < WIDTH; ++j)
        {
            QChar digitChar = line.at(j);
            if (digitChar == '1') {
                brick = new Brick(j * BLOCKUNIT, i * BLOCKUNIT);
                addItem(brick);
            } if (digitChar == '2') {
                Steel *steel = new Steel(j * BLOCKUNIT, i * BLOCKUNIT);
                addItem(steel);
            }
            background_num[i][j] = digitChar.digitValue();
            //qDebug() << background_num[i][j];//array that save the number
        }
    }
    // 关闭文件
    file.close();

    player = new Player();
    player->setPos(250, 250);
    addItem(player);
}

Scene::~Scene()
{
    //delete player;
    //delete timer;
}

void Scene::keyPressEvent(QKeyEvent *event)
{

    QPointF pos = player->pos();

    if (event->key() == Qt::Key_Left && pos.x() > 0) {
        QPointF nextPos = pos + QPointF(-10, 0);
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
            player->setPixmap(QPixmap(":/images/player1_left.png").scaled(45, 45));
            currentDirection = Qt::Key_Left;
        }
    } else if (event->key() == Qt::Key_Right && pos.x() < 600) {
        QPointF nextPos =pos + QPointF(10, 0);
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
            player->setPixmap(QPixmap(":/images/player1_right.png").scaled(45,45));
            currentDirection = Qt::Key_Right;
        }
    } else if (event->key() == Qt::Key_Up && pos.y() > 0) {
        QPointF nextPos = pos + QPointF(0, -10);
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
            player->setPixmap(QPixmap(":/images/player1_up.png").scaled(45, 45));
            currentDirection = Qt::Key_Up;
        }
    } else if (event->key() == Qt::Key_Down) {
        QPointF nextPos = pos + QPointF(0, 10);
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
            player->setPixmap(QPixmap(":/images/player1_down.png").scaled(45, 45));
            currentDirection = Qt::Key_Down;
        }
    } else if (event->key() == Qt::Key_Space) {
        Bullet *bullet = new Bullet(currentDirection);
        bullet->setPos(player->pos() + QPointF(20, 20));
        addItem(bullet);
    }
}

bool Scene::collisionWithObstacle(const QPointF &nextPos, const QPointF &pos)
{
    player->setPos(nextPos);
    QList<QGraphicsItem *> collidingItems = player->collidingItems();
    player->setPos(pos);
    for (QGraphicsItem *item : collidingItems) {
        if (typeid(*item) == typeid(Brick) || typeid(*item) == typeid(Steel) ) {
            return true;
        }
    }
    return false;
}
