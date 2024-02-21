#include "collection.h"
#include <QRandomGenerator>

Collection::Collection(QObject *parent) : QObject(parent), QGraphicsItem()
{
    m_k=0; //переменная определяющая, находится ли данный объект на передднем плане или на заднем
    m_f = QRandomGenerator::global()->bounded(1, 4); //рандомное значение, которое будет определять какую фигуру поместить
};


Collection::~Collection(){}
//далее идет именно процесс создания фигуры
QRectF Collection::boundingRect() const
{
    return QRectF (-30,-30,60,60);
}

void Collection::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::yellow);
        switch(m_f)
        {
            case 1:
                painter->drawRect(-30,-30,60,60);
                break;
            case 2:
                painter->drawEllipse(-30,-30,60,60);
                break;
            case 3:
                QPolygon pol;
                pol << QPoint(-30,30)  <<  QPoint(30,30)<<QPoint(0,-30);
                painter->drawPolygon(pol);
                break;
        }

        Q_UNUSED(option);
        Q_UNUSED(widget);
}

//далее идут ивенты для нажатия мышью
void Collection::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_k ==1)
    {
       this->setPos(mapToScene(event->pos()));
    }
    Q_UNUSED(event);

}

void Collection::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    emit needtoBeFirstLayer(this, m_k);
    Q_UNUSED(event);
}





