#include "scene.h"


void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPos = event->scenePos();
        if (CheckItemPresence()) AddItem();
        ToForeground();
    }
}


void Scene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
     if (event->button() == Qt::LeftButton) {
        QPointF pos = event->scenePos();
        activeItem = itemAt(pos.x(), pos.y(), QTransform());
        if (activeItem) removeItem(activeItem);
    }
}


void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (activeItem && (event->buttons() & Qt::LeftButton)) {
        QPointF pos = event->scenePos();
        QPointF delta = pos - lastPos;
        activeItem->moveBy(delta.x(), delta.y());
        lastPos = pos;
    }
}


void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton) activeItem = nullptr;
}


bool Scene::CheckItemPresence() {
    activeItem = itemAt(lastPos.x(), lastPos.y(), QTransform());
    if (activeItem) return false;
    return true;
}


void Scene::AddItem() {
    int n = QRandomGenerator::global()->bounded(1, 4);

    if (n == 1) AddCircle();
    else if (n == 2) AddTriangle();
    else if (n == 3) AddRectangle();

    activeItem->setPos(lastPos);
    addItem(activeItem);
}


void Scene::ToForeground() {
    maxZValue++;
    activeItem->setZValue(maxZValue);
}


void Scene::AddCircle() {
    int radius = 50;
    activeItem = new QGraphicsEllipseItem(-radius,-radius, radius*2, radius*2);
    QColor color(100, 100, 200);
    static_cast<QGraphicsEllipseItem*>(activeItem)->setBrush(color);
}


void Scene::AddTriangle() {
    int radius = 40;
    QPolygonF triangle;
    triangle << QPointF(0, 0) << QPointF(radius*2, 0) << QPointF(0, radius*2); // Точки задают вершины треугольника
    activeItem = new QGraphicsPolygonItem(triangle);
    QColor color(100, 200, 100);
    static_cast<QGraphicsPolygonItem*>(activeItem)->setBrush(color);
}


void Scene::AddRectangle() {
    int radius = 45;
    activeItem = new QGraphicsRectItem(0, 0, radius*2, radius*2);
    QColor color(200, 100, 100);
    static_cast<QGraphicsRectItem*>(activeItem)->setBrush(color);
}
