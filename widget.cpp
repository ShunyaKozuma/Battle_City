#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget), scene(new Scene(this))
{
    ui->setupUi(this);

    scene->setSceneRect(-12.5, -25, 800, 750);
    scene->setBackgroundBrush(QBrush(Qt::black));

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //連接各種狀態
    connect(scene, &Scene::restartGame, this, &Widget::restartStatement);
    connect(scene, &Scene::pauseGame, this, &Widget::pauseStatement);
    connect(scene, &Scene::continueGame, this, &Widget::continueStatement);
    //scene->startGame();
    //ui->graphicsView->setFixedSize(800,800);

    //background
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
    connect(but2,&QPushButton::clicked,this,&Widget::startButton_clicked);

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
    StartbdSetting();
}



void Widget::continueStatement()
{
    imageLabel->hide();
    PauseNote->hide();
}

void Widget::StartbdSetting()
{

    imageLabel->show();
    but1->show();
    but2->show();
    title->show();
    return;
}

void Widget::startButton_clicked()
{

    but1->hide();
    but2->hide();
    imageLabel->hide();
    title->hide();
    scene->startGame();
    ui->graphicsView->setFocus();//待研究
    qDebug()<<"start to play the game! ";

}
void Widget::pauseStatement()
{

    imageLabel->show();
    PauseNote->show();

}


