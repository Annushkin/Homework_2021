#include "apple.h"

Apple::Apple(QObject *parent): QObject(parent), QGraphicsItem()
{
    color = qrand() % ((3 + 1) - 1) + 1;  //генерация чисел 1, 2, 3 для случайного выбора цвета яблока
}

Apple::~Apple(){}

QRectF Apple::boundingRect() const
{
    return QRectF(-20,-20,40,40);  // Ограничиваем область, в которой лежит яблоко
}

void Apple::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    //рисуем яблоко
    QPainterPath path(QPointF(0,-10));  //Класс QPainterPath предоставляет контейнер
                                        //для операций рисования, позволяя создавать
                                        //и повторно использовать графические формы
                                        //Класс QPointF описывает точку на плоскости
    path.cubicTo(0,-10, -5,-14,  -12,-8); //Это перегруженная функция. Добавляет кубическую кривую Безье
                                          //между текущей позицией и конечной точкой ( endPointX , endPointY )
                                          // с контрольными точками ( c1X , c1Y ) и ( c2X , c2Y ).
    path.cubicTo(-12,-8, -20,12, -10,15);
    path.cubicTo(-10,15, -5,20, 0,16);
    path.cubicTo(0,16, 5,20, 10,15);
    path.cubicTo(10,15, 20,12, 12,-8);
    path.cubicTo(12,-8, 5,-14,  0,-10);

    switch (color)  //устанавливаем цвет кисти
    {
    case 1:
        painter->setBrush(Qt::red);
        break;
    case 2:
        painter->setBrush(Qt::green);
        break;
    case 3:
        painter->setBrush(Qt::yellow);
        break;
    }

    //рисуем хвостик
    painter->drawPath(path);
    painter->setPen(QPen(Qt::black, 2));
    QPainterPath path2(QPointF(0,-10));
    path2.cubicTo(0,-10,4,-18,10,-20);
    painter->setBrush(Qt::NoBrush);
    painter->drawPath(path2);

    //рисуем листик
    painter->setPen(QPen(Qt::black, 1));
    QPainterPath path3(QPointF(0,-10));
    path3.cubicTo(0,-10,-2,-20,-15,-20);
    path3.cubicTo(-15,-20,-14,-12,0,-10);
    painter->setBrush(Qt::green);
    painter->drawPath(path3);

    //отключение неиспользуемых параметров
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

