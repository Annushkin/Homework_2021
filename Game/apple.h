//Клас для отрисовки яблок

#ifndef APPLE_H   //директивы, чтобы избежать множественного включения одного файла.
#define APPLE_H

#include <QObject>       //базовый класс для всех объектов Qt, нужен, например для объявления и связывания
                         //сигналов и слотов (содержит методы coonect, disconnect, event)
#include <QGraphicsItem> //Класс QGraphicsItem является базовым классом
                         //для всех графических элементов в QGraphicsScene.
#include <QGraphicsScene> //Класс QGraphicsScene предоставляет поверхность для управления
                          //большим числом графических 2D элементов.
                          //Этот класс служит как контейнер для QGraphicsItems.
                          //Он используется вместе с QGraphicsView для отображения
                          //графических объектов, таких как линии, прямоугольники
#include <QPainter>       //Обычно QPainter используется внутри события рисования виджета:
                          //создание и настройка (например, установка пера или кисти)

class Apple : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Apple(QObject *parent = 0); //Установка parent в nullptr создаёт объекта без родителя.
                                          //Если объект является виджетом, он станет окном верхнего уровня.
    ~Apple();


public slots:

protected:
    QRectF boundingRect() const; //Эта чисто виртуальная функция определяет внешние границы элемента
                                 //в виде прямоугольника;всё рисование должно быть ограничено внутри
                                 //этого прямоугольника. QGraphicsView использует его для определения
                                 // необходимости перерисовки элемента.
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int color;
};

#endif // APPLE_H
