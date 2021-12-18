#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QObject>//базовый класс для всех объектов Qt, нужен, например для объявления и связывания
                  //сигналов и слотов (содержит методы coonect, disconnect, event)
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>  //Класс событий мыши

class CustomScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CustomScene(QObject *parent = 0);
    ~CustomScene();

signals:
    // Сигнал для передачи координат положения курсора мыши
    void signalTargetCoordinate(QPointF point);

public slots:

private:
    // Функция, в которой производится отслеживание положения мыши
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
   // void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // CUSTOMSCENE_H
