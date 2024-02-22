#include "form.h"


Form::Form(int contactId) {
    dataEntryForm = new QDialog();

    SetTitle(contactId);

    // Создаем компоненты для ввода данных
    nameLineEdit = new QLineEdit(dataEntryForm);
    surnameLineEdit = new QLineEdit(dataEntryForm);
    patronymicLineEdit = new QLineEdit(dataEntryForm);
    addressLineEdit = new QLineEdit(dataEntryForm);
    birthdateEdit = new DateEdit(dataEntryForm);
    emailLineEdit = new QLineEdit(dataEntryForm);
    birthdateEdit->setDateRange(QDate(1900, 1, 1), QDate::currentDate());
    birthdateEdit->setDisplayFormat("dd.MM.yyyy");

    QLabel *nameLabel = new QLabel("Name:", dataEntryForm);
    QLabel *surnameLabel = new QLabel("Surname:", dataEntryForm);
    QLabel *patronymicLabel = new QLabel("Patronymic:", dataEntryForm);
    QLabel *addressLabel = new QLabel("Address:", dataEntryForm);
    QLabel *birthdateLabel = new QLabel("Bithday:", dataEntryForm);
    QLabel *emailLabel = new QLabel("Email:", dataEntryForm);

    phonesLayout = new QVBoxLayout;
    addPhoneButton = new QPushButton("Add phone number", dataEntryForm);
    saveButton = new QPushButton("Save", dataEntryForm);
    saveButton->setStyleSheet("background-color: green;");

    QObject::connect(addPhoneButton, &QPushButton::clicked, [this](){AddPhone();});

    // Создаем макет для формы
    QFormLayout *formLayout = new QFormLayout(dataEntryForm);
    formLayout->addRow(nameLabel, nameLineEdit);
    formLayout->addRow(surnameLabel, surnameLineEdit);
    formLayout->addRow(patronymicLabel, patronymicLineEdit);
    formLayout->addRow(addressLabel, addressLineEdit);
    formLayout->addRow(birthdateLabel, birthdateEdit);
    formLayout->addRow(emailLabel, emailLineEdit);
    formLayout->addRow(phonesLayout);
    formLayout->addRow(addPhoneButton);
    formLayout->addRow(saveButton);

    dataEntryForm->setLayout(formLayout);
}


void Form::SetTitle(int contactId) {
    if (contactId == -1) dataEntryForm->setWindowTitle("New contact creating");
    else dataEntryForm->setWindowTitle(QString("Contact №") + QString::number(contactId) + QString(" change"));
}


void Form::AddPhone(QString phoneType, QString phoneNumber) {
    QComboBox *phoneTypeComboBox = new QComboBox();
    phoneTypeComboBox->addItem("Mobile");
    phoneTypeComboBox->addItem("Home");
    phoneTypeComboBox->addItem("Work");
    phoneTypeComboBox->setCurrentText(phoneType);

    QPushButton *deleteButton = new QPushButton();
    deleteButton->setIcon(QIcon(":/pic/delete.png"));

    QLineEdit *phoneNumberLineEdit = new QLineEdit();
    phoneNumberLineEdit->setText(phoneNumber);

    QWidget *phoneFormWidget = new QWidget();
    QHBoxLayout *phoneFormLayout = new QHBoxLayout();
    phoneFormWidget->setLayout(phoneFormLayout);

    phoneFormLayout->addWidget(deleteButton);
    phoneFormLayout->addWidget(phoneTypeComboBox);
    phoneFormLayout->addWidget(phoneNumberLineEdit);

    phonesLayout->addWidget(phoneFormWidget);

    QObject::connect(deleteButton, &QPushButton::clicked, [this, phoneFormWidget](){
        phonesLayout->removeWidget(phoneFormWidget);
        delete phoneFormWidget;
    });
}

