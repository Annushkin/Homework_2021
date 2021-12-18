//Класс мухи

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QObject> //базовый класс для всех объектов Qt, нужен, например для объявления и связывания
                   //сигналов и слотов (содержит методы coonect, disconnect, event)

#include <QTimer>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#define GO true
#define STOP false

class Triangle : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Triangle();
   // QTimer *gameTimer;      // Игровой таймер
    QMediaPlayer * m_player;        // Аудио плеер
    QMediaPlaylist * m_playlist;    // Плейлист

signals:
   void signalCheckItem(QGraphicsItem *item);

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void slotTarget(QPointF point); // Слот для установки координаты, куда нужно идти
    void slotGameTimer();   // Игровой слот

private:

    QPointF target;         // Положение курсора
    bool state;             // Статус идти/стоять
    int steps;          // Номер положения ножек мухи
    int countForSteps;  // Счётчик для отсчета тиков таймера, при которых мы нажимали на кнопки


};

#endif // TRIANGLE_H
