#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>

class GraphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    GraphicsScene(QWidget *parent=nullptr);

signals:
    void positionMoved(double x, double y);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // GRAPHICSSCENE_H
