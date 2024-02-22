#include "item.h"

#include <QPainter>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>


RectangleItem::RectangleItem(QGraphicsItem* parent): QGraphicsItem(parent) {
}


QRectF RectangleItem::boundingRect() const {
    return QRectF(0, 0, 100, 100); // Задайте размеры прямоугольника
}


void RectangleItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::black);
    painter->setBrush(Qt::blue);
    painter->drawRect(boundingRect());
}


void RectangleItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (boundingRect().contains(event->pos()))
    {
        // Нажатие было внутри прямоугольника
        qDebug() << "Нажатие внутри прямоугольника";
    }
    else
    {
        // Нажатие было на границе прямоугольника
        qDebug() << "Нажатие на границе прямоугольника";
    }
}
