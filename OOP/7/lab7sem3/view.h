#ifndef VIEW_H
#define VIEW_H
#include <QWidget>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include "collection.h"

class Widget : public QWidget
{
    Q_OBJECT
    QPushButton *m_createButton;
    QPushButton *m_deleteButton;
    QPushButton *createButton;
    QPushButton *deleteButton;
    QList<Collection*> ObjectList;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QGraphicsScene *scene;
    QGraphicsView *main;
public slots:
    void create_obj();
    void delete_obj();
    void layOnFirstLayer(Collection *Item , int& k);
};
#endif // VIEW_H
