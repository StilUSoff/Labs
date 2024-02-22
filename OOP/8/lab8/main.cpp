//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);

//    // Создаем главное окно
//    QMainWindow window;
//    window.setFixedSize(635, 600);

//    QWidget* centralWidget = new QWidget(&window);
//    QHBoxLayout* layout = new QHBoxLayout(centralWidget);

//    QTableWidget* table = new QTableWidget(centralWidget);
//    table->setRowCount(4);
//    table->setColumnCount(6);

//    QStringList hLabels;
//    hLabels << "Name" << "Surname" << "Patronymic" << "Address" << "Bithday" << "Phone";
//    table->setHorizontalHeaderLabels(hLabels);

//    layout->addWidget(table);
//    window.setCentralWidget(centralWidget);
//    window.show();

//    return app.exec();
//}

#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
