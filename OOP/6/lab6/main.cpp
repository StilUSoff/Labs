#include "WidgetCollection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetCollection w;
    w.show();
    return a.exec();
}
