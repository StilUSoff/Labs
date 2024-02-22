#include <QGraphicsItem>


class RectangleItem : public QGraphicsItem {

public:
    RectangleItem(QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};
