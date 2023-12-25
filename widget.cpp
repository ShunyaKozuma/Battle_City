#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), scene(new Scene(this))
{
    ui->setupUi(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(800, 700);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //連接各種狀態
    connect(scene, &Scene::restartGame, this, &Widget::restartStatement);//直接重啟狀態(按R)
    connect(scene, &Scene::pauseGame, this, &Widget::pauseStatement);//按暫停鍵狀態(按T)
    connect(scene, &Scene::continueGame, this, &Widget::continueStatement);//暫停後繼續狀態(暫停狀態按T)
    connect(scene, &Scene::finishGame, this, &Widget::ToNextStatement);//完成當前關卡，準備前往下一個關卡
    connect(scene, &Scene::GameOver, this, &Widget::gameoverStatement);//遊戲失敗畫面(未做)

    //background

    scene->setSceneRect(0, 0, 800, 700);
    scene->setBackgroundBrush(QBrush(Qt::black));

    QGraphicsRectItem *grayBackground = new QGraphicsRectItem(650, 0, 150, 700);
    grayBackground->setBrush(QBrush(Qt::gray));
    scene->addItem(grayBackground);

    // scaling
    scene->addLine(0, 0, 650, 0, QPen(Qt::blue));
    scene->addLine(0, 0, 0, 700, QPen(Qt::red));
    scene->addLine(650, 0, 650, 700, QPen(Qt::blue));
    scene->addLine(650, 700, 0, 700, QPen(Qt::blue));


    imageLabel=new QLabel(this);
    QPixmap image(":/images/brick_background.jpg"); // 请替换为实际图片路径
    imageLabel->setPixmap(image);
    imageLabel->setGeometry(0,0,image.width(), image.height());

    //player1、2
    but1=new QPushButton("player1",this);
    but1->move(200,400);
    but1->setStyleSheet("player1{font:20px;}");
    but1->resize(100,50);
    connect(but1,&QPushButton::clicked,this,&Widget::startButton_clicked);

    but2=new QPushButton("player2",this);
    but2->move(500,400);
    but2->setStyleSheet("player2{font:20px;}");
    but2->resize(100,50);
    connect(but2,&QPushButton::clicked,this,&Widget::TwoPlayerstartButton_clicked);

    title=new QLabel("Battle City!", this);
    QFont font("Press Start 2P", 80, QFont::Bold);
    title->setStyleSheet("color: white; ");
    title->setFont(font);
    title->setGeometry(150, 50, 550, 200);

    PauseNote=new QLabel("push key T to continue the game!", this);
    QFont font1("Press Start 2P", 20, QFont::Bold);
    PauseNote->setStyleSheet("color: white; ");
    PauseNote->setFont(font1);
    PauseNote->setGeometry(150, 50, 550, 200);
    PauseNote->hide();//先不出現

    //gameover重新開始介面
    restartbut=new QPushButton("Play Again",this);
    restartbut->move(400,400);
    restartbut->setStyleSheet("Play Again{font:20px;}");
    restartbut->resize(200,100);
    connect(restartbut,&QPushButton::clicked,this,&Widget::gameoverButton_clicked);
    restartbut->hide();

    //下一關過度介面
    nextbut=new QPushButton("GO NEXT",this);
    nextbut->move(400,400);
    nextbut->setStyleSheet("Play Again{font:20px;}");
    nextbut->resize(200,100);
    connect(nextbut,&QPushButton::clicked,this,&Widget::NextButton_clicked);//
    nextbut->hide();

    //統計分數的頁面
    scorestorebut=new QPushButton("Rank",this);
    scorestorebut->move(500,250);
    scorestorebut->setStyleSheet("Rank{font:20px;}");
    //scorestorebut->resize(200,100);
    connect(scorestorebut,&QPushButton::clicked,this,&Widget::rankButton_clicked);
    scorestorebut->hide();

    //統計分數的頁面返回介面返回鍵
    returnfromrank =new QPushButton("return",this);
    returnfromrank->move(650,600);
    //returnfromrank->setStyleSheet("Rank{font:20px;}");
    //returnfromrank->resize(100,100);
    connect(returnfromrank,&QPushButton::clicked,this,&Widget::returnButton_clicked);
    returnfromrank->setStyleSheet("");
    returnfromrank->hide();

    //分數統計表格
    tableWidget = new QTableWidget;
    tableWidget->hide();




}

Widget::~Widget()
{
    delete ui;
    delete imageLabel;
    delete title;
    delete but2;
    delete but1;
}


void Widget::restartStatement()
{
    //qDebug()<<"widget restarting....";
    scene->clear();//移除场景中的所有图形项
    qDebug()<<"widget cleared";
    QGraphicsRectItem *grayBackground = new QGraphicsRectItem(650, 0, 150, 700);
    grayBackground->setBrush(QBrush(Qt::gray));
    scene->addItem(grayBackground);
    StartbdSetting();
}



void Widget::continueStatement()
{
    imageLabel->hide();
    PauseNote->hide();
}

void Widget::gameoverStatement()
{

    restartbut->show();
}

void Widget::ToNextStatement()
{
    nextbut->show();//一顆繼續玩下一關，等下一關準備製作再開始
    //要顯示當局分數統計
    //另一顆按鈕一顆繼續玩下一關，一顆顯示回去主畫面

}

void Widget::StartbdSetting()
{

    imageLabel->show();
    but1->show();
    but2->show();
    title->show();
    scorestorebut->show();
    return;
}

void Widget::TotalScoreRank()
{
    //包函分數、秒數以及是否破關
}

void Widget::ranktablesetting()
{
    int rowCount = scene->ScoreRecord.size();
    int colCount = 2;  // 假设有两列
    // 创建一个表格用于显示分数统计表
    //QTableWidget *tableWidget = new QTableWidget(rowCount, colCount, this);
    tableWidget->setRowCount(rowCount);
    tableWidget->setColumnCount(colCount);
    tableWidget->setParent(this);
    tableWidget->setGeometry(50, 50, 300, 200);
    tableWidget->setHorizontalHeaderLabels({"Score", "Total Playtime(s)"});
    //data
    for (int row = 0; row < rowCount; ++row) {
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(scene->ScoreRecord[row].first));
        QTableWidgetItem *timeItem = new QTableWidgetItem(QString::number(scene->ScoreRecord[row].second));

        tableWidget->setItem(row, 0, scoreItem);
        tableWidget->setItem(row, 1, timeItem);
    }
    tableWidget->setGeometry(50, 50, 300, 200);

    // 显示表格
    tableWidget->show();
}

void Widget::startButton_clicked()
{

    scene->Player2Exist=0;//沒有存在第二個玩家
    but1->hide();
    but2->hide();
    imageLabel->hide();
    title->hide();
    scorestorebut->hide();
    scene->startGame();
    ui->graphicsView->setFocus();//待研究
    qDebug()<<"start to play the game! ";

}

void Widget::TwoPlayerstartButton_clicked()
{
    scene->Player2Exist=1;
    but1->hide();
    but2->hide();
    imageLabel->hide();
    title->hide();
    scorestorebut->hide();
    scene->startGame();
    scene->AddOnePlayer();
    ui->graphicsView->setFocus();//待研究
    qDebug()<<"2player";
}

void Widget::gameoverButton_clicked()
{
    restartbut->hide();
    restartStatement();
}

void Widget::rankButton_clicked()
{
    but1->hide();
    but2->hide();
    //imageLabel->hide();
    title->hide();
    scorestorebut->hide();
    returnfromrank->show();
    ranktablesetting();//顯示所有局數分數統計表
}

void Widget::returnButton_clicked()
{

    returnfromrank->hide();
    tableWidget->hide();//統計表消失
    StartbdSetting();

}

void Widget::NextButton_clicked()
{
    nextbut->hide();
    restartStatement();

}
void Widget::pauseStatement()
{

    //imageLabel->show();
    PauseNote->show();

}


