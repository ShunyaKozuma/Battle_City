#include "widget.h"
#include "ui_widget.h"


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
    //ui->graphicsView->setFixedSize(800,800);
}

Widget::~Widget()
{
    delete ui;
}


