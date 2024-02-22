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


class SearchForm {

public:
    SearchForm();

    QLineEdit *nameLineEdit;
    QLineEdit *surnameLineEdit;
    QLineEdit *patronymicLineEdit;
    QLineEdit *addressLineEdit;
    DateEdit *birthdateEdit;
    QLineEdit *emailLineEdit;
    QLineEdit *phoneLineEdit;

    QDialog *dataEntryForm;
    QPushButton *applyButton;
    QPushButton *clearButton;
};
