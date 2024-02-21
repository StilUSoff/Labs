#ifndef VIEW_H
#define VIEW_H
#include <QPushButton>
#include <QTableWidget>
#include <QStringList>
#include <QCalendarWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMainWindow>
#include<QLineEdit>
#include<QHeaderView>
#include <QDateEdit>
#include <QFile>
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
class View:public QMainWindow
{
    Q_OBJECT
public:
//конструктор_________________
    View(QWidget *parent = nullptr);
//кнопочки___________________
    QPushButton *createButton;
    QPushButton *deleteButton;
    QPushButton *fileButton;
    QPushButton *fromfileButton;
    QPushButton *searchButton;
//поле_______________________
    QGridLayout *mainBox;
    QWidget* cent_widget;
    QLineEdit* lineEdit;
    QLineEdit* lineEdit2;
    QLineEdit* lineEdit3;
    QString startString;
    QLabel *pred;
//таблица ___________________
    QTableWidget* table;
//деструктор__________________
    virtual ~View() {};
//проверочки
    bool Name(QString &name);
    bool Phone(QString &phone);
    bool Email(QString &email);

public slots:

    void createButtonClicked();
    void deleteButtonClicked();
    void searchButtonClicked();
    void fileButtonClicked();
    void fromfileButtonClicked();
    void Saver(int,int);
    void Checked(int,int);
    void setTextSlot(const QDate& date);
};


#endif // VIEW_H
