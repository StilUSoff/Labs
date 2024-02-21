#include "mainwindow.h"
#include "WidgetCollection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Collection w;
    w.show();
    return a.exec();
}
