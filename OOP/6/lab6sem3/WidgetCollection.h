#ifndef WIDGETCOLLECTION_H
#define WIDGETCOLLECTION_H
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>
#include <QScrollBar>
#include <QRandomGenerator>
#include <QHBoxLayout>
#include <AddLabel.h>
#include <QDial>
#include <QAbstractSlider>
enum members { Qlabel =1, Qslider = 2, Qscrollbar = 3,Qspinbox = 4, Qdial = 5 };
class Collection:public QWidget
{
    Q_OBJECT
private:
    void ConnectWidget();
public:
    Collection(QWidget *parent = nullptr);
    ~Collection();
    int value;
    QPushButton *createButton;
    QPushButton *deleteButton;
    QVBoxLayout *mainBox;
    QList<QWidget*> WidgetList;

signals:
    void valueChanged(int val);
public slots:
    void setValue(int i);
    void create_obj();
    void delete_obj();
};


#endif // WIDGETCOLLECTION_H
