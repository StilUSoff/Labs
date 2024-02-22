#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include "scene.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QGraphicsView view;
    view.setFixedSize(1000, 700);
    Scene scene;
    scene.setSceneRect(0,  0, 1000, 700);

    view.setScene(&scene);
    view.setRenderHint(QPainter::Antialiasing);
    view.setBackgroundBrush(QBrush(Qt::white));

    view.show();

    return app.exec();
}
