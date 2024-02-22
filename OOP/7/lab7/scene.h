#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include <QPolygonF>
#include <QPen>
#include <QBrush>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPointF>
#include <QColor>

#include "item.h"


class Scene : public QGraphicsScene
{
public:
    Scene() {
        maxZValue = 0;
        activeItem = nullptr;
    }

private:
    QGraphicsItem *activeItem;
    QPointF lastPos;
    int maxZValue;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    bool CheckItemPresence();
    void AddItem();
    void ToForeground();

    void AddRectangle();
    void AddTriangle();
    void AddCircle();

};
