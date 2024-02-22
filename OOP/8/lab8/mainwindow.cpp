#include "mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setWindowTitle("Пример ввода данных на Qt");
    setFixedSize(770, 600);

    stackedWidget = new QStackedWidget();

    QWidget *tableWidget = new QWidget(this);
    QVBoxLayout *tableLayout = new QVBoxLayout(tableWidget);
    tableWidget->setLayout(tableLayout);

    NewSearchForm();
    CreateMenu();
    CreateBar();
    CreateTable();

    tableLayout->addWidget(bar);
    tableLayout->addWidget(table);

    stackedWidget->addWidget(menu);
    stackedWidget->addWidget(tableWidget);

    stackedWidget->setCurrentIndex(0);

    setCentralWidget(stackedWidget);
}


void MainWindow::CreateTable() {
    table = new QTableWidget(this);
    table->setRowCount(0);
    table->setColumnCount(7);

    QStringList hLabels;
    hLabels << "Name" << "Surname" << "Patronymic" << "Address" << "Bithday" << "Email" << "Phones";
    table->setHorizontalHeaderLabels(hLabels);
    table->setColumnWidth(3, 120);
    table->setColumnWidth(4, 65);
    table->setColumnWidth(6, 150);

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSortingEnabled(true);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    table->setShowGrid(true);

    connect(table, &QTableWidget::itemDoubleClicked, this, EditContact);
}


void MainWindow::CreateBar() {
    bar = new QWidget(this);
    QHBoxLayout *barLayout =  new QHBoxLayout(bar);
    bar->setLayout(barLayout);

    QPushButton *newContactButton = new QPushButton("New", bar);
    QPushButton *deleteContactButton = new QPushButton("Delete", bar);
    QPushButton *searchContactButton = new QPushButton("Search", bar);
    QPushButton *saveButton = new QPushButton("Save", bar);
    QPushButton *closeButton = new QPushButton("Close", bar);

    barLayout->addWidget(newContactButton);
    barLayout->addWidget(deleteContactButton);
    barLayout->addWidget(searchContactButton);
    barLayout->addWidget(saveButton);
    barLayout->addWidget(closeButton);

    connect(newContactButton, &QPushButton::clicked, this, NewContact);
    connect(deleteContactButton, &QPushButton::clicked, this, DeleteContacts);
    connect(searchContactButton, &QPushButton::clicked, this, ShowSearchForm);
    connect(saveButton, &QPushButton::clicked, this, SaveToFile);
    connect(closeButton, &QPushButton::clicked, this, ToMenu);
}


void MainWindow::CreateMenu() {
    menu = new QWidget(this);
    QVBoxLayout *menuLayout =  new QVBoxLayout(menu);
    menuLayout->setAlignment(Qt::AlignCenter);
    menu->setLayout(menuLayout);

    QPushButton *newButton = new QPushButton("Новый справочник", menu);
    QPushButton *importButton = new QPushButton("Импорт из файла", menu);

    menuLayout->addWidget(newButton);
    menuLayout->addWidget(importButton);

    connect(newButton, &QPushButton::clicked, this, NewTable);
    connect(importButton, &QPushButton::clicked, this, ImportFromFile);
}


MainWindow::~MainWindow() {

}


void MainWindow::NewContact() {
    currentRow = -2;
    NewForm();
    ShowForm();
}


void MainWindow::SaveContact() {
    QString error = ValidateFormData();

    if (!(error == QString(""))) {
        ShowErrorMessage(error);
        return;
    }

    if (currentRow == -2) {
        currentRow = table->rowCount();
        table->insertRow(currentRow);
    }

    FormToTableRow();
    table->update();
    HideForm();
}


void MainWindow::ShowForm() {
    form->dataEntryForm->exec();
}


void MainWindow::ShowSearchForm() {
    searchForm->dataEntryForm->exec();
}


void MainWindow::HideForm() {
    form->dataEntryForm->accept();
}


void MainWindow::HideSearchForm() {
    searchForm->dataEntryForm->accept();
}


QString MainWindow::ValidateFormData() {
    QString name = form->nameLineEdit->text();
    if (!validator.isValidName(name)) return QString("<b>Name is valid!</b> It can contain only letters and numbers of different alphabets, a hyphen and a space. It must start with letters only, and cannot end or begin with a hyphen.");
    form->nameLineEdit->setText(name);

    QString surname = form->surnameLineEdit->text();
    if (!validator.isValidName(surname)) return QString("<b>Surname is valid!</b> It can contain only letters and numbers of different alphabets, a hyphen and a space. It must start with letters only, and cannot end or begin with a hyphen.");
    form->surnameLineEdit->setText(surname);

    QString patronymic = form->patronymicLineEdit->text();
    if (!validator.isValidName(patronymic)) return QString("<b>Patronymic is valid!</b> It can contain only letters and numbers of different alphabets, a hyphen and a space. It must start with letters only, and cannot end or begin with a hyphen.");
    form->patronymicLineEdit->setText(patronymic);

    QString email = form->emailLineEdit->text();
    if (!validator.isValidEmail(email)) return QString("<b>Email is valid!</b> It must contain a user name consisting of Latin letters and numbers, a symbol separating the user and the domain name (@), as well as the domain itself consisting of Latin letters and numbers.");
    form->emailLineEdit->setText(email);

    for (int i = 0; i < form->phonesLayout->count(); i++) {
        QLineEdit *phoneLineEdit = dynamic_cast<QLineEdit*>(dynamic_cast<QWidget*>(form->phonesLayout->itemAt(i)->widget())->layout()->itemAt(2)->widget());
        QString phone = phoneLineEdit->text();
        if (!validator.isValidPhone(phone)) return QString("<b>Phone number is valid!</b> It must be in an international format: +X-XXX-XXXX-XXXX");
        phoneLineEdit->setText(phone);
    }

    return QString("");
}


bool MainWindow::CheckRowBySearch(int rowId) {
    QString text;

    text = searchForm->nameLineEdit->text();
    if (!((text == QString("")) || (text == table->item(rowId, 0)->text()))) return false;

    text = searchForm->surnameLineEdit->text();
    if (!((text == QString("")) || (text == table->item(rowId, 1)->text()))) return false;

    text = searchForm->patronymicLineEdit->text();
    if (!((text == QString("")) || (text == table->item(rowId, 2)->text()))) return false;

    text = searchForm->addressLineEdit->text();
    if (!((text == QString("")) || (text == table->item(rowId, 3)->text()))) return false;

    text = searchForm->birthdateEdit->text();
    if (!((text == QString("")) || (text == table->item(rowId, 4)->text()))) return false;

    text = searchForm->emailLineEdit->text();
    if (!((text == QString("")) || (text == table->item(rowId, 5)->text()))) return false;

    text = searchForm->phoneLineEdit->text();
    if (text != QString("")) {
        QStringList phones = table->item(rowId, 6)->text().split("\n");

        bool wasFound = false;
        for (int i = 0; i < phones.size(); ++i) {
            QStringList phoneParts = phones.at(i).split(": ");
            if (phoneParts[1] == text) {wasFound = true; break;};
        };

        if (!wasFound) return false;
    };

    return true;
}


void MainWindow::ShowErrorMessage(const QString text) {
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.setWindowTitle("Error");
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.exec();
}


void MainWindow::NewForm() {
    form = new Form(currentRow + 1);
    connect(form->saveButton, &QPushButton::clicked, this, SaveContact);
}


void MainWindow::NewSearchForm() {
    searchForm = new SearchForm();
    connect(searchForm->applyButton, &QPushButton::clicked, this, SearchContacts);
    connect(searchForm->clearButton, &QPushButton::clicked, this, ClearSearchForm);
}


void MainWindow::EditContact(QTableWidgetItem* item) {
    currentRow = table->currentRow();
    table->selectRow(currentRow);
    NewForm();
    TableRowToForm();
    ShowForm();
}


void MainWindow::FormToTableRow() {
    table->setItem(currentRow, 0, new QTableWidgetItem(form->nameLineEdit->text()));
    table->setItem(currentRow, 1, new QTableWidgetItem(form->surnameLineEdit->text()));
    table->setItem(currentRow, 2, new QTableWidgetItem(form->patronymicLineEdit->text()));
    table->setItem(currentRow, 3, new QTableWidgetItem(form->addressLineEdit->text()));
    table->setItem(currentRow, 4, new QTableWidgetItem(form->birthdateEdit->date().toString("dd.MM.yyyy")));
    table->setItem(currentRow, 5, new QTableWidgetItem(form->emailLineEdit->text()));

    QString phonesCellText = QString("");
    for (int i = 0; i < form->phonesLayout->count(); i++) {
        QWidget* phoneWidget = dynamic_cast<QWidget*>(form->phonesLayout->itemAt(i)->widget());
        QComboBox *phoneTypeComboBox = dynamic_cast<QComboBox *>(phoneWidget->layout()->itemAt(1)->widget());
        QLineEdit *phoneNumberLineEdit = dynamic_cast<QLineEdit*>(phoneWidget->layout()->itemAt(2)->widget());
        phonesCellText += phoneTypeComboBox->currentText() + QString(": ") + phoneNumberLineEdit->text();
        if (i != form->phonesLayout->count() - 1)  phonesCellText += QString("\n");
    }

    table->setItem(currentRow, 6, new QTableWidgetItem(phonesCellText));
}


void MainWindow::TableRowToForm() {
    form->nameLineEdit->setText(table->item(currentRow, 0)->text());
    form->surnameLineEdit->setText(table->item(currentRow, 1)->text());
    form->patronymicLineEdit->setText(table->item(currentRow, 2)->text());
    form->addressLineEdit->setText(table->item(currentRow, 3)->text());
    form->birthdateEdit->setDate(QDate::fromString(table->item(currentRow, 4)->text(), "dd.MM.yyyy"));
    form->emailLineEdit->setText(table->item(currentRow, 5)->text());

    QString phonesCellText = table->item(currentRow, 6)->text();
    if (phonesCellText != QString("")) {
        QStringList phones = phonesCellText.split("\n");
        for (int i = 0; i < phones.size(); ++i) {
            QStringList phoneParts = phones.at(i).split(": ");
            form->AddPhone(phoneParts[0], phoneParts[1]);
        }
    }
}


void MainWindow::DeleteContacts() {
    for (int row = table->rowCount() - 1; row >= 0; row--) {

        bool isSelected = true;

        for (int col = 0; col < table->columnCount(); col++) {
            QTableWidgetItem *item = table->item(row, col);
            if (item && !item->isSelected()) {
                isSelected = false;
                break;
            }
        }

        if (isSelected) {
            table->removeRow(row);
        }
    }
}


void MainWindow::SearchContacts() {
    for (int row = 0; row < table->rowCount(); ++row) {
        table->setRowHidden(row, !CheckRowBySearch(row));
    }
    HideSearchForm();
}

void MainWindow::ClearSearchForm() {
    for (int row = 0; row < table->rowCount(); ++row) {
        table->setRowHidden(row, false);
    }
    HideSearchForm();
    NewSearchForm();
}


void MainWindow::ClearTable() {
    for (int row = table->rowCount() - 1; row >= 0; row--) table->removeRow(row);
}


void MainWindow::SaveToFile() {
    QString fileName = QFileDialog::getSaveFileName(nullptr, "Сохранить файл", "", "Текстовые файлы (*.txt);;Все файлы (*.*)");

    if (fileName.isEmpty()) return;

    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Fail while open file";
        return;
    }

    TableToFile(&file);
    file.close();
    qDebug() << "Success";
}



void MainWindow::ImportFromFile() {
    QString fileName = QFileDialog::getOpenFileName(nullptr, "Открыть файл", "", "Текстовые файлы (*.txt);;Все файлы (*.*)");

    if (fileName.isEmpty()) return;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly  | QIODevice::Text)) {
        qDebug() << "Fail while open file";
        return;
    }

    FileToTable(&file);
    file.close();

    stackedWidget->setCurrentIndex(1);
    qDebug() << "Success";
}


void MainWindow::TableToFile(QFile *file) {
    QTextStream out(file);
    for (int row = 0; row < table->rowCount(); ++row) {
        for (int column = 0; column < table->columnCount(); ++column) {

            QTableWidgetItem *item = table->item(row, column);

            QString text = item->text();
            QString subStr("\n");
            QString newStr(";");
            text.replace(text.indexOf(subStr), subStr.size(), newStr);

            if (item) out << text << "\t";
        }
        out << "\n";
    }
}


void MainWindow::FileToTable(QFile *file) {
    QTextStream in(file);
    ClearTable();

    int row = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList items = line.split("\t", Qt::SkipEmptyParts);
        table->insertRow(row);

        for (int column = 0; column < items.size(); ++column) {

            QString text = items[column];
            QString subStr(";");
            QString newStr("\n");
            text.replace(text.indexOf(subStr), subStr.size(), newStr);

            table->setItem(row, column, new QTableWidgetItem(text));
        }
        ++row;
    }
}


void MainWindow::NewTable() {
    ClearTable();
    stackedWidget->setCurrentIndex(1);
}


void MainWindow::ToMenu() {
    stackedWidget->setCurrentIndex(0);
}
