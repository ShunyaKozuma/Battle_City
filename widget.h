#ifndef WIDGET_H
#define WIDGET_H

#include "Scene.h"
#include <QWidget>
#include<QPushButton>
#include<QLabel>
#include <QTableWidget>
#include <QTableWidgetItem>
QT_BEGIN_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void StartbdSetting();
    void TotalScoreRank();
    void saveDataToTxt();


private:
    Ui::Widget *ui;
    Scene *scene;

    //用來處理封面的標題啥的
    QLabel *imageLabel;
    QLabel *title;
    QLabel *PauseNote;
    QPushButton *but1;
    QPushButton *but2;
    QPushButton *restartbut;
    QPushButton *scorestorebut;
    QPushButton *returnfromrank;
    QPushButton *nextbut;
    //QPushButton *save;
    QPushButton *exitGamebut;
    QPushButton *loadOldGamebut;
    void ranktablesetting();
    QTableWidget *tableWidget;
    QPushButton *NewGamebut;

    //QGraphicsRectItem *grayBackground;
    //signals:
    //    void on_startButton_clicked();
public slots:
    void startButton_clicked();
    void TwoPlayerstartButton_clicked();
    void gameoverButton_clicked();
    void rankButton_clicked();
    void returnButton_clicked();
    void NextButton_clicked();
    void restartStatement();
    void pauseStatement();
    void continueStatement();
    void gameoverStatement();
    void ToNextStatement();
    void loadOldGame_clicked();
    void exitGame_clicked();//離開遊戲自動存起來
    void choosePlayerStatement();

};
#endif // WIDGET_H
