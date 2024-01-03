#include "Scene.h"
#include <QApplication>
#include <QString>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QList>
#include <QStringList>
// file operation
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QResource>
#include <QDebug>
#include <QTimer>
#include <QElapsedTimer>
#include <algorithm>
#include <ctime>
#include <random>


//player只能有一個子彈(如果子彈在gameover的情況下被打到一次頁面會crashed)
//還沒有做雙人版被敵方打到單人死亡的狀況(目前的寫法是只要打到player就直接gameover)
//還沒有寫ice(如果在冰面上的話要按一次移動兩部(會打滑))
Scene::Scene(QObject *parent)
    : QGraphicsScene{parent}
{


}

void Scene::startGame(){

    CurrentStatus=2;//遊戲狀態為正在進行中
    setGameOn(true);
    if (gameLevel==1){
        resourcePath = ":/word/obstacle.txt";
    }else if(gameLevel==2){
        resourcePath = ":/word/obstacle2.txt";}//第二關地圖，要改把下面那條comment
    //QString resourcePath = ":/word/obstacle.txt";

    QResource::registerResource("res.qrc");
    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file: " << file.errorString();
        //return 1;
    }

    QTextStream in(&file); // 创建QTextStream对象，并将其与文件关联

    // 读取文件内容
    for (int i = 0; i < HEIGHT; ++i)
    {
        QString line = in.readLine();
        for (int j = 0; j < WIDTH; ++j)
        {
            QChar digitChar = line.at(j);
            if (digitChar == '1') {
                brick = new Brick(j * BLOCKUNIT, i * BLOCKUNIT);
                addItem(brick);
            } if (digitChar == '2') {
                steel = new Steel(j * BLOCKUNIT, i * BLOCKUNIT);
                addItem(steel);
            }
            if (digitChar == '3') {
                tree = new Trees(j * BLOCKUNIT, i * BLOCKUNIT);
                addItem(tree);}
            if (digitChar == '4') {
                water = new Water(j * BLOCKUNIT, i * BLOCKUNIT);
                addItem(water);}
            if (digitChar == '5') {
                ice = new Ice(j * BLOCKUNIT, i * BLOCKUNIT);
                addItem(ice);}
            background_num[i][j] = digitChar.digitValue();
            //qDebug() << background_num[i][j];//array that save the number
        }
    }
    file.close();

    player = new Player();
    //player_health--;
    player->setPos(250, 250);
    addItem(player);

    score = new Score();
    addItem(score);

    eagle = new Eagle();
    eagle->setPos(300,650);
    addItem(eagle);


    //set the amount of the enemy tanks
    tanknum = 12;
    enemyLife = tanknum;

    for(int i=0; i<tanknum; i++){
        EnemyHealth* enemyHealth = new EnemyHealth();
        enemyHealth->setPos(680 + i%2 * 40 ,150 + i/2 * 40);
        enemyHealthList.append(enemyHealth);
        addItem(enemyHealth);
    }

    random_factor=rand()%1000+5000;
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Scene::randomGenerateEnemyStart );
    timer->start(random_factor);

    //場景計時器
    totalplaytime=0;
    updateTimer = new QTimer();
    connect(updateTimer, &QTimer::timeout, this, &Scene::UpdateGameTimer);
    updateTimer->start(1000);
    timerDisplay = new QGraphicsTextItem();
    timerDisplay->setFont(QFont("times",16));
    timerDisplay->setDefaultTextColor(Qt::black);
    timerDisplay->setPos(680, 50);
    addItem(timerDisplay);

    //1012顯示health
    //totalplaytime=0;
    //updateTimer = new QTimer();
    //connect(updateTimer, &QTimer::timeout, this, &Scene::UpdateGameTimer);
    //updateTimer->start(1000);
    player_health=3;
    healthDisplay = new QGraphicsTextItem();
    healthDisplay->setFont(QFont("times",16));
    healthDisplay->setDefaultTextColor(Qt::black);
    healthDisplay->setPos(680, 500);
    addItem(healthDisplay);
    QString healthString = QString("Health: %1").arg(player_health);
    healthDisplay->setPlainText(healthString);
    //0102



    //玩家數量(預設1)
    playerNumber=1;
}

Scene::~Scene()
{

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
        AddNewRecord();
        BeforeNextPage();
        /*
        foreach(QGraphicsItem *item, items()) {

            if (Bullet *item = dynamic_cast<Bullet*>(item)) {
                // 执行 freezeInPlace 方法
                removeItem(item);
                delete item;
            }
        }
        */
        emit restartGame(); // 发送重新开始游戏的信号
    }else if(event->key() == Qt::Key_T && CurrentStatus==2) {//如果現在狀態是正常運行且暫停鍵被按下，執行暫停模式
        CurrentStatus=3;//變成暫停狀態3
        timer->stop();
        updateTimer->stop();
        freezeAllItem();

        emit pauseGame();

    }else if (event->key() == Qt::Key_T && CurrentStatus==3){
        qDebug() << "use key_T again to cancel pausing the game: ";
        CurrentStatus=2;
        timer->start();
        updateTimer->start();
        defreezeAllItem();//凍結頁面所有物體(但目前bullet卡bug)
        emit continueGame();

        //tank->defreeze();

    }else if (event->key() == Qt::Key_Left && pos.x() > 0 && CurrentStatus==2) {
        QPointF nextPos = pos + QPointF(-10, 0);
        player->setPixmap(QPixmap(":/images/player1_left.png").scaled(40, 40));
        currentDirection = Qt::Key_Left;
        nextPos=detectIceCollision(nextPos,pos);
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
        }
    } else if (event->key() == Qt::Key_Right && pos.x() < 600 && CurrentStatus==2) {
        QPointF nextPos =pos + QPointF(10, 0);

        player->setPixmap(QPixmap(":/images/player1_right.png").scaled(40,40));
        currentDirection = Qt::Key_Right;
        nextPos=detectIceCollision(nextPos,pos);
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
        }
    } else if (event->key() == Qt::Key_Up && pos.y() > 0 && CurrentStatus==2) {
        QPointF nextPos = pos + QPointF(0, -10);
        player->setPixmap(QPixmap(":/images/player1_up.png").scaled(40, 40));
        currentDirection = Qt::Key_Up;
        nextPos=detectIceCollision(nextPos,pos);
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
        }
    } else if (event->key() == Qt::Key_Down && pos.y() < 650 && CurrentStatus==2) {

        QPointF nextPos = pos + QPointF(0, 10);
        player->setPixmap(QPixmap(":/images/player1_down.png").scaled(40, 40));
        currentDirection = Qt::Key_Down;
        nextPos=detectIceCollision(nextPos,pos);
        if (!collisionWithObstacle(nextPos,pos)) {
            player->setPos(nextPos);
        }
    } else if (event->key() == Qt::Key_Space && CurrentStatus==2 && (currentplayerbullet==nullptr || player_conti_shoot)) {
        if(player_bullet_max==2) return;
        if(player_conti_shoot == true )
            player_bullet_max++;
        Player_Bullet *bullet = new Player_Bullet(currentDirection,player_bulletspeedbuff,player_bulletpowerbuff);
        currentplayerbullet = bullet;
        connect(currentplayerbullet,&Player_Bullet::playerbulletgone,this,&Scene::setCPBnull);
        connect(bullet, &Bullet::bulletHitEnemy, this, &Scene::decreaseEnemyHealth);
        connect(bullet, &Bullet::LosePlayerLife, this, &Scene::LosePLayerToScene);//1225新增，己方子彈打到輸掉遊戲
        connect(bullet, &Bullet::bulletHitFlashing, this, &Scene::getPowerUps);
        connect(bullet, &Bullet::addscroe,this,&Scene::increaseScore);
        connect(bullet, &Bullet::GG, this, &Scene::Eagle_dead);
        bullet->setPos(player->pos() + QPointF(20, 20));
        addItem(bullet);
    }
    /*
    if (event->key() == Qt::Key_E ){//測試用，直接全部結束遊戲
    //   變成可以存檔的按鍵
        emit
        BeforeNextPage();
        emit GameOver();
    }
        //邏輯: 再暫停狀態中直接連接gameover(待寫，gameover畫面包含遊戲統計分數)->暫停狀態按r再繞回初始介面並更改CurrentStatus=1
    //}
    */



    //直接複製貼上的方式做的，如果可以用其他更好的方式再刪
    if (Player2Exist) {
        QPointF pos2 = player2->pos();
        if (event->key() == Qt::Key_A && pos2.x() > 0 && CurrentStatus==2) {
            QPointF nextPos2 = pos2 + QPointF(-10, 0);
            player2->setPixmap(QPixmap(":/images/player2_left.png").scaled(40, 40));
            currentDirection2 = Qt::Key_Left;
            nextPos2=detectIceCollision(nextPos2,pos2,2);
            if (!collisionWithObstacle(nextPos2,pos2,2)) {
                player2->setPos(nextPos2);
            }
        } else if (event->key() == Qt::Key_D && pos2.x() < 600 && CurrentStatus==2) {
            QPointF nextPos2 =pos2 + QPointF(10, 0);

            player2->setPixmap(QPixmap(":/images/player2_right.png").scaled(40,40));
            currentDirection2 = Qt::Key_Right;
            nextPos2=detectIceCollision(nextPos2,pos2,2);
            if (!collisionWithObstacle(nextPos2,pos2,2)) {
                player2->setPos(nextPos2);
            }
        } else if (event->key() == Qt::Key_W && pos2.y() > 0 && CurrentStatus==2) {
            QPointF nextPos2 = pos2 + QPointF(0, -10);
            player2->setPixmap(QPixmap(":/images/player2_up.png").scaled(40, 40));
            currentDirection2 = Qt::Key_Up;
            nextPos2=detectIceCollision(nextPos2,pos2,2);
            if (!collisionWithObstacle(nextPos2,pos2,2)) {
                player2->setPos(nextPos2);
            }
        } else if (event->key() == Qt::Key_S && pos2.y() < 650 && CurrentStatus==2) {

            QPointF nextPos2 = pos2 + QPointF(0, 10);
            player2->setPixmap(QPixmap(":/images/player2_down.png").scaled(40, 40));
            currentDirection2 = Qt::Key_Down;
            nextPos2=detectIceCollision(nextPos2,pos2,2);
            if (!collisionWithObstacle(nextPos2,pos2,2)) {
                player2->setPos(nextPos2);
            }
        } else if (event->key() == Qt::Key_Q && CurrentStatus==2) {
            Player_Bullet *bullet = new Player_Bullet(currentDirection2,player_bulletspeedbuff,player_bulletpowerbuff);
            currentplayerbullet = bullet;
            //connect(currentplayerbullet,&Player_Bullet::playerbulletgone,this,&Scene::setCPBnull);
            connect(currentplayerbullet, &Player_Bullet::playerbulletgone,this,&Scene::setCPBnull);
            connect(bullet, &Bullet::bulletHitEnemy, this, &Scene::decreaseEnemyHealth);
            connect(bullet, &Bullet::LosePlayerLife, this, &Scene::LosePLayerToScene);
            connect(bullet, &Bullet::bulletHitFlashing, this, &Scene::getPowerUps);
            connect(bullet, &Bullet::addscroe,this,&Scene::increaseScore);
            connect(bullet, &Bullet::GG, this, &Scene::Eagle_dead);
            bullet->setPos(player2->pos() + QPointF(20, 20));
            addItem(bullet);
        }

    }
    //player2到這邊結束

}

bool Scene::collisionWithObstacle(const QPointF &nextPos, const QPointF &pos,int playernum)
{
    if(playernum==1){
        player->setPos(nextPos);
        QList<QGraphicsItem *> collidingItems = player->collidingItems();
        player->setPos(pos);
        for (QGraphicsItem *item : collidingItems) {
            if (typeid(*item) == typeid(Brick) || typeid(*item) == typeid(Steel)||typeid(*item) == typeid(Water) ) {
                return true;
            }
            //if(typeid(*item) == typeid(Ice)){
                //nextPos=nextPos*2;
                //return ;
            //}
        }
        return false;
    }else if (playernum==2){//player2的判斷代碼，前面要刪後面跟著刪
        player2->setPos(nextPos);
        QList<QGraphicsItem *> collidingItems = player2->collidingItems();
        player2->setPos(pos);
        for (QGraphicsItem *item : collidingItems) {
            if (typeid(*item) == typeid(Brick) || typeid(*item) == typeid(Steel) ||typeid(*item) == typeid(Water)) {
                return true;
            }
        }
        return false;
    }
}

//create collisionWithPowerUps later

void Scene::randomGenerateEnemyStart()
{
    if (tanknum) {
        tanknum--;
        if (tanknum == 1 || tanknum == 3 || tanknum == 6 || tanknum == 9) {
            Enemy* flashing = new Flashing();  // Allocate on the heap
            flashing->setPos(rand() % 600, 0);
            addItem(flashing);
            connect(flashing, Enemy::TellSceneLosePlayer, this, &Scene::LosePLayerToScene);
        } else {
            Enemy* enemy = nullptr;
            switch (rand() % 4)
            {
            case 0: enemy = new Basic(); break;
            case 1: enemy = new Fast(); break;
            case 2: enemy = new Power(); break;
            case 3: enemy = new Armor(); break;
            }
            if(rand() % 2){
                enemy->setPos(rand() % 600, 0);
            }else{
                if(rand() % 2)
                    enemy->setPos(600, 300);
                else
                    enemy->setPos(50 , 350);
            }
            addItem(enemy);
            connect(enemy, Enemy::TellSceneLosePlayer, this, &Scene::LosePLayerToScene);
        }
        delete enemyHealthList.takeLast();
    }
}


//decrease enemy health and increase score
//renew, actually the health is showed the reamind unmber of enemy tanks, it is not health tho
void Scene::decreaseEnemyHealth()
{
    enemyLife--;
    checkEnemyDeath();
}

void Scene::checkEnemyDeath(){
    if (enemyHealthList.isEmpty() && enemyLife <= 0) {
        //跳到遊戲結束畫面
        CurrentStatus = 4;
        defreezeAllItem();
        AddNewRecord();
        BeforeNextPage();
        gameLevel++;
        if(gameLevel>2){//如果大於目前關卡數量
            gameLevel=1;//回到第一關
        }
        freezeAllItem();
        emit finishGame();
    }
}

void Scene::getPowerUps(){
    PowerUp::PowerUpType randomType = PowerUp::Grenade;
    //PowerUp::PowerUpType randomType = static_cast< PowerUp::PowerUpType>(rand() % 6);
    PowerUp* powerUp = new PowerUp(randomType);
    connect(powerUp, &PowerUp::collected, this, &Scene::usePowerUps);
    bool hasCollision = false;
    do {
        hasCollision = false;
        powerUp->setPos(rand() % 600, rand() % 650);
        for (QGraphicsItem* item : collidingItems(powerUp)) {
            if (typeid(*item) == typeid(Steel) || typeid(*item) == typeid(Water)) {
                hasCollision = true;
                break;
            }
        }
    } while (hasCollision);

    addItem(powerUp);
}

void Scene::usePowerUps(const PowerUp::PowerUpType type)
{
    switch (type) {
    case PowerUp::Grenade:{
            //qDebug() << "hit buff is heeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeer";
            QList<QGraphicsItem *> items = this->items();
            for (QGraphicsItem *item : items) {
                if (Enemy *enemy = dynamic_cast<Enemy*>(item)) {
                    // Destroy the enemy
                    score->increase(enemy->getscore());
                    enemyLife--;
                    removeItem(item);
                    delete item;
                }
            }
            checkEnemyDeath();
            break;
        }
        case PowerUp::Helmet:
        {
            //Later add a helmet effection pic for players
            QList<QGraphicsItem *> items = this->items();
            for (QGraphicsItem *item : items) {
                if (Enemy *enemy = dynamic_cast<Enemy*>(item)) {
                    invinciable = new QTimer();
                    enemy->sethelmet();
                    connect(invinciable, &QTimer::timeout,[=](){
                        qDebug()<<"fuck";
                        enemy->unsethelmet();
                        invinciable->stop();
                    });
                    invinciable->start(10000);
                }
            }
            break;
        }
        case PowerUp::Shovel:{
            //11~14 26,27,28
            for(int i = 11; i < 15; i++) {
                for(int j = 25; j < 28; j++) {
                    if(background_num[j][i] == 1) {
                        Steel* tempsteel = new Steel(i * BLOCKUNIT, j * BLOCKUNIT);
                        addItem(tempsteel);

                        QTimer::singleShot(5000, [=]() {
                            Brick* recoverbrick = new Brick(i * BLOCKUNIT, j * BLOCKUNIT);
                            addItem(recoverbrick);
                            removeItem(tempsteel);
                            delete tempsteel;
                        });
                    }
                }
            }
            break;
        }
        case PowerUp::Star:
        {
                /*
            if(player_status==1)
            {
                qDebug()<<"player_status==1";
                player_bulletspeedbuff=3;
                player_status=2;
                break;
            }

            if(player_status==2)
            {
                player_conti_shoot=true;
                player_bullet_max=0;
                player_status=3;
                break;
            }

            if(player_status==3)
            {
                player_bulletpowerbuff=true;
                player_status=3;
                break;
            }
            */
        }
        case PowerUp::Tank:
        {
            player_health++;
            QString healthString = QString("Health: %1").arg(player_health);
            healthDisplay->setPlainText(healthString);
            break;
        }
        case PowerUp::Timer:{
            QList<QGraphicsItem *> items = this->items();
            for (QGraphicsItem *item : items) {
                if (Enemy *enemy = dynamic_cast<Enemy*>(item)) {
                    // stop enemy in the scene
                    enemy->stopEnemyTank();
                }
            }
            break;
        }
// Add cases for other power-up types
    }
}

void Scene::LosePLayerToScene()
{
    player_health--;
    QString healthString = QString("Health: %1").arg(player_health);
    healthDisplay->setPlainText(healthString);
    if(player_health==0)
    {

        CurrentStatus=4;
        freezeAllItem();
        AddNewRecord();
        BeforeNextPage();

        emit GameOver();
    }else{
        removeItem(player);
        delete(player);
        player = new Player();
        player->setPos(250, 250);
        addItem(player);
    }
}


void Scene::UpdateGameTimer()
{
    totalplaytime=totalplaytime+1;
    QString timeString = QString("Time: %1s").arg(totalplaytime);
    timerDisplay->setPlainText(timeString);
}

void Scene::setCPBnull()
{
    if(currentplayerbullet!=nullptr)
        currentplayerbullet=nullptr;
    if(player_conti_shoot) player_bullet_max--;
}

void Scene::increaseScore(int point)
{
    score->increase(point);
}

void Scene::Eagle_dead()
{
    CurrentStatus=4;
    freezeAllItem();
    AddNewRecord();
    BeforeNextPage();

    emit GameOver();
}

void Scene::AddNewRecord()
{
    ScoreRecord.append(QPair<int, int>(score->getScore(), totalplaytime));
    std::sort(ScoreRecord.begin(), ScoreRecord.end(), [](const QPair<int, int> &a, const QPair<int, int> &b) {
        return a.first > b.first;
    });
}
void Scene::BeforeNextPage(){
    updateTimer->stop();
    delete updateTimer;
    delete timer;
    removeItem(timerDisplay);
    delete timerDisplay;
}

void Scene::AddOnePlayer()
{
    playerNumber=2;
    player2 = new Player();
    player2->setPos(0, 600);
    addItem(player2);
    player2->setPixmap((QPixmap(":/images/player2_up.png").scaled(40,40)));
}

void Scene::freezeAllItem()
{
    foreach(QGraphicsItem *item, items()) {

        if (Enemy *enemy = dynamic_cast<Enemy*>(item)) {
                // 执行 freezeInPlace 方法
                enemy->stopEnemyTank();
        }else if(Player_Bullet *pbullet = dynamic_cast<Player_Bullet*>(item)){
                pbullet->freezeInPlace();
        }else if(Enemy_Bullet *ebullet = dynamic_cast<Enemy_Bullet*>(item)){
                ebullet->freezeInPlace();
        }
    }
}

void Scene::defreezeAllItem()
{
    foreach(QGraphicsItem *item, items()) {
        if (Enemy *enemy = dynamic_cast<Enemy*>(item)) {
                // 执行 freezeInPlace 方法
                enemy->defreeze();
        }else if(Player_Bullet *pbullet = dynamic_cast<Player_Bullet*>(item)){
                pbullet->defreeze();
        }else if(Enemy_Bullet *ebullet = dynamic_cast<Enemy_Bullet*>(item)){
                ebullet->defreeze();
        }
    }
}

QPointF Scene::detectIceCollision(const QPointF &nextPos, const QPointF &pos, int playernum)
{
    QPointF doublePos=nextPos;
    if(playernum==1){
        //QPointF originPos=doublePos;
        player->setPos(nextPos);
        QList<QGraphicsItem *> collidingItems = player->collidingItems();
        player->setPos(pos);
        for (QGraphicsItem *item : collidingItems) {
                if (typeid(*item) == typeid(Ice) ) {
                    doublePos=(doublePos-pos)*1.5+pos;
                    return doublePos;
                }
        }
    }else if (playernum==2){//player2的判斷代碼，前面要刪後面跟著刪
        player2->setPos(nextPos);
        QList<QGraphicsItem *> collidingItems = player2->collidingItems();
        player2->setPos(pos);
        for (QGraphicsItem *item : collidingItems) {
                if (typeid(*item) == typeid(Ice) ) {
                    doublePos=(doublePos-pos)*1.5+pos;
                    return doublePos;
                }
        }
    }
    return nextPos;
}


void Scene::saveAllRecord()//
{

    //playerNumber;//當前玩家數量
    //gameLevel;//當前關卡位置
    //player->pos();//當下玩家位置
    //player->x();
    //if(playerNumber==2){
    //    player2->pos();
    //}
    //player_health;//當前生命值
    //totalplaytime;
    //qDebug()<<playerNumber;
    //qDebug()<<gameLevel;
    //qDebug()<<player->pos();

    //qDebug()<<"hehehehhehheh";

    //QResource::registerResource("res.qrc");
    //QString resourcePath = ":/word/obstacle.txt";
    //QString filename2 = ":/word/RecordForOldGame.txt";
    saveRecordPath = "C:/Users/NUTC/OneDrive/桌面/RecordForOldGame.txt";
    QFile file(saveRecordPath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "無法打開文件：" << file.errorString();
        return;
        // 適當地處理錯誤，返回或顯示一條消息。
    } else {

        QTextStream out(&file);
        //0-5儲存這些變數
        out << playerNumber << " " << gameLevel << " " << player->x() << " " << player->y() << " " << player_health << " " << totalplaytime << " ";

        //6-7儲存是否有第二個玩家
        if (playerNumber == 2) {
                out << player2->x() << " " << player2->y() << " ";
        }//else{
        //        out << 999 << " " << 999 << " ";
        //}

        out << "\n";
        qDebug() << "文件寫入成功";

        file.close();
    }
}

void Scene::getOldRecord()
{

    saveRecordPath = "C:/Users/NUTC/OneDrive/桌面/RecordForOldGame.txt";
    QFile file(saveRecordPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "無法打開文件：" << file.errorString();
                                               return;
        // 適當地處理錯誤，返回或顯示一條消息。
    } else {

        QTextStream in(&file);
        QString lastLine;
        while (!in.atEnd()) {
                lastLine = in.readLine();
        }
        QStringList values = lastLine.split(' ', Qt::SkipEmptyParts);

        if (values.size() >= 6) { // 确保至少有六个值
                //playerNumber = values[0].toInt();
                gameLevel = values[1].toInt();
                startGame();
                playerNumber = values[0].toInt();
                player->setX(values[2].toInt());
                player->setY(values[3].toInt());
                player_health = values[4].toInt();
                totalplaytime = values[5].toInt();
                Player2Exist=0;

                qDebug() << "Values read from file:";
                qDebug() << "playerNumber: " << playerNumber;
                qDebug() << "gameLevel: " << gameLevel;
                qDebug() << "player->x(): " << player->x();
                qDebug() << "player->y(): " << player->y();
                qDebug() << "player_health: " << player_health;
                qDebug() << "totalplaytime: " << totalplaytime;
        } else {
                qDebug() << "文件格式错误：未找到足够的值。";
        }
        //if (values[6].toInt() != 999){//6、7
        if (values.size() >= 7) {
                AddOnePlayer();
                player2->setX(values[6].toInt());
                player2->setY(values[7].toInt());
                Player2Exist=1;
        }

        file.close();

        //out << "\n";
        qDebug() << "文件寫入成功";


    }
}





