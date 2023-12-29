#ifndef WIDGET_H
#define WIDGET_H

#include "Scene.h"
#include <QWidget>
#include<QPushButton>
#include<QLabel>
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

private:
    Ui::Widget *ui;
    Scene *scene;

    //用來處理封面的標題啥的
    QLabel *imageLabel;
    QLabel *title;
    QLabel *PauseNote;
    QPushButton *but1;
    QPushButton *but2;
    //signals:
    //    void on_startButton_clicked();
public slots:
    void startButton_clicked();
    void restartStatement();
    void pauseStatement();
    void continueStatement();

};
#endif // WIDGET_H
