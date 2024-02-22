#include "searchform.h"


SearchForm::SearchForm() {
    dataEntryForm = new QDialog();
    dataEntryForm->setWindowTitle(QString("Search"));

    QFormLayout *formLayout = new QFormLayout(dataEntryForm);
    dataEntryForm->setLayout(formLayout);

    // Создаем компоненты для ввода данных
    nameLineEdit = new QLineEdit(dataEntryForm);
    surnameLineEdit = new QLineEdit(dataEntryForm);
    patronymicLineEdit = new QLineEdit(dataEntryForm);
    addressLineEdit = new QLineEdit(dataEntryForm);
    birthdateEdit = new DateEdit(dataEntryForm);
    emailLineEdit = new QLineEdit(dataEntryForm);
    birthdateEdit->setDateRange(QDate(1900, 1, 1), QDate::currentDate());
    birthdateEdit->setDisplayFormat("dd.MM.yyyy");
    phoneLineEdit = new QLineEdit(dataEntryForm);

    QLabel *nameLabel = new QLabel("Name:", dataEntryForm);
    QLabel *surnameLabel = new QLabel("Surname:", dataEntryForm);
    QLabel *patronymicLabel = new QLabel("Patronymic:", dataEntryForm);
    QLabel *addressLabel = new QLabel("Address:", dataEntryForm);
    QLabel *birthdateLabel = new QLabel("Bithday:", dataEntryForm);
    QLabel *emailLabel = new QLabel("Email:", dataEntryForm);
    QLabel *phoneLabel = new QLabel("Phone:", dataEntryForm);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    applyButton = new QPushButton("Apply", dataEntryForm);
    clearButton = new QPushButton("Clear", dataEntryForm);
    buttonsLayout->addWidget(applyButton);
    buttonsLayout->addWidget(clearButton);

    formLayout->addRow(nameLabel, nameLineEdit);
    formLayout->addRow(surnameLabel, surnameLineEdit);
    formLayout->addRow(patronymicLabel, patronymicLineEdit);
    formLayout->addRow(addressLabel, addressLineEdit);
    formLayout->addRow(birthdateLabel, birthdateEdit);
    formLayout->addRow(emailLabel, emailLineEdit);
    formLayout->addRow(phoneLabel, phoneLineEdit);
    formLayout->addRow(buttonsLayout);
}

