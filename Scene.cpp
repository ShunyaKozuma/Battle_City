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
#include <QTimer>
#include <QElapsedTimer>

//把介面與timer的部分搞定(暫停尚無法跟著暫停)
//子彈碰撞坦克生命值delete以及直接結束遊戲
Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{

}

void Scene::startGame(){

    CurrentStatus=2;//遊戲狀態為正在進行中
    setGameOn(true);
    QString resourcePath = ":/word/obstacle.txt";
    QResource::registerResource("res.qrc");
    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file: " << file.errorString();
        //return 1;
    }

    QTextStream in(&file); // 创建QTextStream对象，并将其与文件关联

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

    /*
    QList<QGraphicsItem*> itemsList = items(); // 获取场景中的所有项

      // 遍历项，查找是否有Player对象
    foreach (QGraphicsItem* item, itemsList) {
        if(typeid(item)==typeid(Player)){
        //if (item->type() == Player()) { // 假设PlayerType是Player的类型ID
            Player* existingPlayer = qgraphicsitem_cast<Player*>(item);
            if (existingPlayer) {
                qDebug() << "removeItem(existingPlayer);";
                removeItem(existingPlayer);
                delete existingPlayer;
                break;  // 找到并删除一个Player对象后就退出循环
            }
        }
    }
    */

    player = new Player();
    player->setPos(250, 250);
    addItem(player);

    basic = new Basic();
    basic->setPos(250,0);
    addItem(basic);

    updateTimer = new QTimer();
    gametimer=new QElapsedTimer();
    connect(updateTimer, &QTimer::timeout, this, &Scene::UpdateGameTimer);
    updateTimer->start(500);
    gametimer->start();
    pausedTime=0;
    timerDisplay = new QGraphicsTextItem();
    addItem(timerDisplay);
    //UpdateGameTimer();




    /*
    fast = new Fast();
    fast->setPos(350,0);
    addItem(fast);

    power = new Power();
    power->setPos(450,50);
    addItem(power);

    armor = new Armor();
    armor->setPos(550,0);
    addItem(armor);
*/
}

Scene::~Scene()
{
    //delete player;
    //delete timer;
    //delete basic;
    /*
    delete fast;
    delete power;
    delete armor;
    */
}

bool Scene::getGameOn() const
{
    return gameOn;
}

void Scene::setGameOn(bool newGameOn)
{
    gameOn = newGameOn;
}

void Scene::keyPressEvent(QKeyEvent *event)
{

    QPointF pos = player->pos();

    if (event->key() == Qt::Key_R && CurrentStatus==2) {
        CurrentStatus=1;//初始遊戲畫面的狀態
        qDebug() << "restart: ";

        //將計時器全部刪掉
        updateTimer->stop();
        delete updateTimer;
        delete gametimer;
        removeItem(timerDisplay);
        delete timerDisplay;

        emit restartGame(); // 发送重新开始游戏的信号
    }else if(event->key() == Qt::Key_T && CurrentStatus==2) {//如果現在狀態是正常運行且暫停鍵被按下，執行暫停模式
        CurrentStatus=3;//變成暫停狀態3
        pausedTime = gametimer->elapsed();
        qDebug()<<"pausedTime"<<pausedTime;
        emit pauseGame();

        //timer->stop();有的話要停止!
        //tank freezeInPlace();

    }else if (event->key() == Qt::Key_T && CurrentStatus==3){
        qDebug() << "use key_T again to cancel pausing the game: ";
        CurrentStatus=2;
        gametimer->restart();//bug QQ

        emit continueGame();
        //tank->defreeze();

    }else if (event->key() == Qt::Key_Left && pos.x() > 0 && CurrentStatus==2) {
        QPointF nextPos = pos + QPointF(-10, 0);
        player->setPixmap(QPixmap(":/images/player1_left.png").scaled(40, 40));
        currentDirection = Qt::Key_Left;
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
        }
    } else if (event->key() == Qt::Key_Right && pos.x() < 600 && CurrentStatus==2) {
        QPointF nextPos =pos + QPointF(10, 0);

        player->setPixmap(QPixmap(":/images/player1_right.png").scaled(40,40));
        currentDirection = Qt::Key_Right;
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
        }
    } else if (event->key() == Qt::Key_Up && pos.y() > 0 && CurrentStatus==2) {
        QPointF nextPos = pos + QPointF(0, -10);
        player->setPixmap(QPixmap(":/images/player1_up.png").scaled(40, 40));
        currentDirection = Qt::Key_Up;
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
        }
    } else if (event->key() == Qt::Key_Down && CurrentStatus==2) {

        QPointF nextPos = pos + QPointF(0, 10);
        player->setPixmap(QPixmap(":/images/player1_down.png").scaled(40, 40));
        currentDirection = Qt::Key_Down;
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
        }
    } else if (event->key() == Qt::Key_Space && CurrentStatus==2) {
        int ExistMyBullet=0;
        foreach (QGraphicsItem *item,items()) {
            if(typeid(*item) == typeid(Player_Bullet)){
                ExistMyBullet=1;
                break;
            }}
        if( ExistMyBullet==0){//如果目前場上無己方子彈
            Player_Bullet *bullet = new Player_Bullet(currentDirection);
            bullet->setPos(player->pos() + QPointF(20, 20));
            addItem(bullet);}
    }
    if (event->key() == Qt::Key_E && CurrentStatus==3){
        CurrentStatus=4;
        //邏輯: 再暫停狀態中直接連接gameover(待寫，gameover畫面包含遊戲統計分數)->暫停狀態按r再繞回初始介面並更改CurrentStatus=1
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


void Scene::UpdateGameTimer()
{   qint64 elapsedMilliseconds = gametimer->elapsed();
    int elapsedSeconds = elapsedMilliseconds / 1000;
    if (pausedTime>0) {
        elapsedSeconds=elapsedSeconds+pausedTime;//question
        pausedTime = 0;  // 重置暂停时间失敗
        qDebug()<<"elapsedSeconds"<<elapsedSeconds;
    }
    //顯示目前開始至今時間
    QString timeString = QString("Time: %1s").arg(elapsedSeconds);
    timerDisplay->setDefaultTextColor(Qt::white);
    timerDisplay->setPlainText(timeString);
    timerDisplay->setPos(600, 0);
    timerDisplay->show();
}

/*
void Scene::LiveMinus()
{
    CurrentStatus=1;//初始遊戲畫面的狀態
    qDebug() << "restart: ";

    //將計時器全部刪掉
    updateTimer->stop();
    delete updateTimer;
    delete gametimer;
    removeItem(timerDisplay);
    delete timerDisplay;

    emit restartGame();
}
*/
