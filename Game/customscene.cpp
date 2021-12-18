#include "customscene.h"
#include <QApplication>

CustomScene::CustomScene(QObject *parent) :
    QGraphicsScene(parent)
{

}

CustomScene::~CustomScene()
{

}

void CustomScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(QApplication::mouseButtons() == Qt::LeftButton){  //Нажата левая кнопка мыши
        emit signalTargetCoordinate(event->scenePos()); // Передаём данный о местоположении клика
                                                 //Возвращает положение курсора мыши в координатах сцены.
    }
}
/*
void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(QApplication::mouseButtons() == Qt::LeftButton){
        emit signalTargetCoordinate(event->scenePos()); // Передаём данный о местоположении клика
    }
}
**/
