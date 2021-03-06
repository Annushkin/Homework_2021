//Класс мухи

#include "triangle.h"
#include <math.h>

#include <QPainter>

static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)  //qreal - псевдоним для double
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Triangle::Triangle()
    : QGraphicsObject()
{
    setRotation(0);

    state = STOP;

    steps = 1;            // Задаём стартовое положение ножек мухи
    countForSteps = 0;    // Счётчик для отсчета тиков таймера, при которых мы нажимали на кнопки
    m_player = new QMediaPlayer(this);          // Инициализация плеера
    m_playlist = new QMediaPlaylist(m_player);  // Инициализация плейлиста
    m_player->setPlaylist(m_playlist);          // Установка плейлиста в аудио плеер
    m_playlist->addMedia(QUrl("qrc:/gamesound/bzzz.wav"));       // Добавление трека в плейлист
    m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop); // Зацикливание трека
}

QRectF Triangle::boundingRect() const
{
    return QRectF(-40,-50,80,100);
}

void Triangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Рисуем ножки, без ножек же муха не сможет ползать
        painter->setPen(QPen(Qt::black, 2));
        if(steps == 0){     // Первое положение ножек
            // Left 1
            painter->drawLine(-24,-37,-22,-25);
            painter->drawLine(-22,-25,-17,-15);
            painter->drawLine(-17,-15,-10,-5);
            // Right 1
            painter->drawLine(37,-28,28,-18);
            painter->drawLine(28,-18,24,-8);
            painter->drawLine(24,-8,10,-5);

            // Left 2
            painter->drawLine(-35,-20,-25,-11);
            painter->drawLine(-25,-11,-14,-5);
            painter->drawLine(-14,-5,0,5);
            // Right 2
            painter->drawLine(37,-12,32,-4);
            painter->drawLine(32,-4,24,2);
            painter->drawLine(24,2,0,5);

            // Left 3
            painter->drawLine(-35,35,-26,24);
            painter->drawLine(-26,24,-16,16);
            painter->drawLine(-16,16,0,0);
            // Right 3
            painter->drawLine(37,26,32,17);
            painter->drawLine(32,17,24,8);
            painter->drawLine(24,8,0,0);
        } else if (steps == 1){     // Второе положение ножек
            // Left 1
            painter->drawLine(-32,-32,-25,-22);
            painter->drawLine(-25,-22,-20,-12);
            painter->drawLine(-20,-12,-10,-5);
            // Right 1
            painter->drawLine(32,-32,25,-22);
            painter->drawLine(25,-22,20,-12);
            painter->drawLine(20,-12,10,-5);

            // Left 2
            painter->drawLine(-39,-15,-30,-8);
            painter->drawLine(-30,-8,-18,-2);
            painter->drawLine(-18,-2,0,5);
            // Right 2
            painter->drawLine(39,-15,30,-8);
            painter->drawLine(30,-8,18,-2);
            painter->drawLine(18,-2,0,5);

            // Left 3
            painter->drawLine(-39,30,-30,20);
            painter->drawLine(-30,20,-20,12);
            painter->drawLine(-20,12,0,0);
            // Right 3
            painter->drawLine(39,30,30,20);
            painter->drawLine(30,20,20,12);
            painter->drawLine(20,12,0,0);
        } else if (steps == 2){     // Третье положение ножек
            // Left 1
            painter->drawLine(-37,-28,-28,-18);
            painter->drawLine(-28,-18,-24,-8);
            painter->drawLine(-24,-8,-10,-5);
            // Right 1
            painter->drawLine(24,-37,22,-25);
            painter->drawLine(22,-25,17,-15);
            painter->drawLine(17,-15,10,-5);

            // Left 2
            painter->drawLine(-37,-12,-32,-4);
            painter->drawLine(-32,-4,-24,2);
            painter->drawLine(-24,2,0,5);
            // Right 2
            painter->drawLine(35,-20,25,-11);
            painter->drawLine(25,-11,14,-5);
            painter->drawLine(14,-5,0,5);

            // Left 3
            painter->drawLine(-37,26,-32,17);
            painter->drawLine(-32,17,-24,8);
            painter->drawLine(-24,8,0,0);
            // Right 3
            painter->drawLine(35,35,26,24);
            painter->drawLine(26,24,16,16);
            painter->drawLine(16,16,0,0);
        }
        // Усики
        QPainterPath path(QPointF(-5,-34));
        path.cubicTo(-5,-34, 0,-36,0,-30);
        path.cubicTo(0,-30, 0,-36,5,-34);
        painter->setBrush(Qt::NoBrush);
        painter->drawPath(path);

        painter->setPen(QPen(Qt::black, 1));
        // Тушка
        painter->setBrush(Qt::black);
        painter->drawEllipse(-15, -20, 30, 50);
        // Голова
        painter->drawEllipse(-15, -30, 30, 20);
        // Глазища
        painter->setBrush(Qt::green);
        painter->drawEllipse(-15, -27, 12, 15);
        painter->drawEllipse(3, -27, 12, 15);

        // Левое крылище
        QPainterPath path2(QPointF(-10, -10));
        path2.cubicTo(-18, -10, -30, 10, -25, 35);
        path2.cubicTo(-25,35,-20,50,-15,40);
        path2.cubicTo(-15,40,0,20,-3,5 );
        path2.cubicTo(-3,5, -8,8,-10,-10);
        painter->setBrush(Qt::white);
        painter->drawPath(path2);

        // Правое крылище
        QPainterPath path3(QPointF(10, -10));
        path3.cubicTo(18, -10, 30, 10, 25, 35);
        path3.cubicTo(25,35,20,50,15,40);
        path3.cubicTo(15,40,0,20,3,5 );
        path3.cubicTo(3,5, 8,8,10,-10);
        painter->setBrush(Qt::white);
        painter->drawPath(path3);

        Q_UNUSED(option);
        Q_UNUSED(widget);

}

void Triangle::slotGameTimer()
{


    if(state){
        //mapFromScene Возвращает точку координат сцены в координаты окна просмотра.
        //Класс QLineF предоставляет двумерный вектор
        QLineF lineToTarget(QPoint(0,0), mapFromScene(target));
        if(lineToTarget.length() > 2){
             setPos(mapToParent(0, -2));



        // Двигаем ноги мухи
        //update(QRectF(-40,-50,80,100)) перерисовка области, покрытой прямоугольником в этом элементе.
                countForSteps++;
                if(countForSteps == 4){
                    steps = 2;
                    update(QRectF(-40,-50,80,100));
                } else if (countForSteps == 8){
                    steps = 1;
                    update(QRectF(-40,-50,80,100));
                } else if (countForSteps == 12){
                    steps = 0;
                    update(QRectF(-40,-50,80,100));
                } else if (countForSteps == 16) {
                    steps = 1;
                    update(QRectF(-40,-50,80,100));
                    countForSteps = 0;
                }

            }

        /* Производим проверку на то, наткнулась ли муха на какой-нибудь элемент на графической сцене.
            Для этого определяем небольшую треугольную область перед мухой, в которой будем искать элементы * */

        //Складываем найденные объекты в контейнер foundItems
        QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                                   << mapToScene(0, 0)
                                                                   << mapToScene(-20, -20)
        /* Получив сигнал от Мухи
           Перебираем весь список яблок и удаляем найденное яблоко * */                                                           << mapToScene(20, -20));
        foreach (QGraphicsItem *item, foundItems) {
                if (item == this)
                    continue;
                emit signalCheckItem(item);
            }

        /* Проверка выхода за границы поля
         Если объект выходит за заданные границы, то возвращаем его назад * */
        if(this->x() - 10 < -250){
            this->setX(-240);         /// слева
            state = STOP;           // Останавливаемся
        }
        if(this->x() + 10 > 250){
            this->setX(240);   /// справа
            state = STOP;           // Останавливаемся
        }

        if(this->y() - 10 < -250){
            this->setY(-240);         /// сверху
            state = STOP;           // Останавливаемся
        }
        if(this->y() + 10 > 250){
            this->setY(240);   /// снизу
            state = STOP;           // Останавливаемся
        }

        m_player->play();   // Плеер играет только тогда, когда муха движется
    } else {
        m_player->stop();   // Если Муха не движется, то отключаем плее
    }

}

void Triangle::slotTarget(QPointF point)
{
    // Определяем расстояние до цели
    target = point;
    QLineF lineToTarget(QPointF(0, 0), mapFromScene(target));
    // Угол поворота в направлении к цели
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    // Поворачиваем героя к цели
    if (angleToTarget >= 0 && angleToTarget < Pi) {
        // Rotate left
        setRotation(rotation() - angleToTarget * 180 /Pi);
    } else if (angleToTarget <= TwoPi && angleToTarget > Pi) {
        // Rotate right
        setRotation(rotation() + (angleToTarget - TwoPi )* (-180) /Pi);
    }

    state = GO; // Разрешаем идти
}

