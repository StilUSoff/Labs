#ifndef COLLECTION_H
#define COLLECTION_H
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include<QGraphicsRectItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

class Collection:  public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Collection(QObject *parent = 0);
    ~Collection();
    int m_k;
private:
    int m_f;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
 signals:
    void needtoBeFirstLayer(Collection* item, int& k);

};

#endif // COLLECTION_H
