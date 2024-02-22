#include <QObject>
#include <QWidget>
#include <QObject>
#include <QWidget>
#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDateEdit>
#include <QComboBox>
#include <QDialog>
#include <QMessageBox>
#include <QGridLayout>
#include <QObject>
#include <map>
#include "dateedit.h"

using namespace std;


class Form {

private:
    void DeletePhone(QPushButton *deleteButton);
    void SetTitle(int contactId);

public:
    Form(int contactId=-1);

    QLineEdit *nameLineEdit;
    QLineEdit *surnameLineEdit;
    QLineEdit *patronymicLineEdit;
    QLineEdit *addressLineEdit;
    DateEdit *birthdateEdit;
    QLineEdit *emailLineEdit;
    QVBoxLayout *phonesLayout;

    QDialog *dataEntryForm;
    QPushButton *saveButton;
    QPushButton *addPhoneButton;

    void AddPhone(QString phoneType = "Mobile", QString phoneNumber = "");
};
