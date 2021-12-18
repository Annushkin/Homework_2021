#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QGraphicsScene>
//#include <QGraphicsItem>
#include <QShortcut>
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include <customscene.h>
#include <triangle.h>
#include <apple.h>
#include <spider.h>

#define GAME_STOPED 0
#define GAME_STARTED 1

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    double count = 1;

signals:
    void signalCheckGameOver();  // Сигнал на вызов состояния Game Over

private:
    Ui::Widget      *ui;     //объявляем окно
    CustomScene     *scene;  //объявляем графическую сцену
    Triangle        *triangle;  //объявляем муху
    QTimer          *timer;    //объявляем таймер
    QTimer          *timerCreateApple;   //таймер созданя яблок
    QList<QGraphicsItem *> apples;    //список яблок

    Spider          *spider;        // Объект Паука
  // QShortcut       *pauseKey;
     int             gameState;    //состояние игры


private slots:
    void slotDeleteApple(QGraphicsItem * item);  //удаление яблок, звук хрум-хрум, увеличение счётчика
    void slotCreateApple();                      //создание яблок
    void on_pushButton_clicked();                //нажание на кнопку "старт"
    void slotGameOver();                         //завершение игры  "вас съели"
    void slotWin();                              //завершение игры "вы выиграли"
   // void slotPause();
};

#endif // WIDGET_H
