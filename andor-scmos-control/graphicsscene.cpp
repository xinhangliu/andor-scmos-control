#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QWidget * parent): QGraphicsScene(parent) {}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QPointF p = event->scenePos();
    double x = p.x();
    double y = p.y();
    emit this->positionMoved(x, y);
    //std::cout << x << ":" << y << std::endl;
}
