#include "view.h"

View::View(QWidget *parent):QMainWindow(parent)
{
      setFixedSize(950,510);
      mainBox = new QGridLayout;


      table = new QTableWidget;
      createButton = new QPushButton("Добавить контакт");
      deleteButton = new QPushButton("Удалить контакт");
      fileButton = new QPushButton("Записать в файл");
      fromfileButton = new QPushButton("Считать из файла");
      searchButton = new QPushButton("Найти контакт");
      pred = new QLabel("Для записи в файл контакта, убедитесь, что номер и его ФИО записаны корректно!");
      cent_widget = new QWidget;
      lineEdit = new QLineEdit;
      lineEdit3 = new QLineEdit;
      lineEdit2 = new QLineEdit;

      connect(createButton, SIGNAL(clicked()), this, SLOT(createButtonClicked()));
      connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteButtonClicked()));
      connect(searchButton, SIGNAL(clicked()), this, SLOT(searchButtonClicked()));
      connect(fileButton, SIGNAL(clicked()), this, SLOT(fileButtonClicked()));
      connect(fromfileButton, SIGNAL(clicked()), this, SLOT(fromfileButtonClicked()));
      table->setColumnCount(5);
      table->setHorizontalHeaderLabels(QStringList{"ФИО", "Адрес", "Дата рождения"," e-mail", "Мобильный телефон"});
      table->setSortingEnabled(true);

      table->setSelectionBehavior(QAbstractItemView::SelectRows);

      table->horizontalHeader()->setStretchLastSection(true);

      mainBox->addWidget(table,0,0,1,5);
      mainBox->addWidget(createButton,1,0);
      mainBox->addWidget(deleteButton,2,0);
      mainBox->addWidget(searchButton,2,4);


      mainBox->addWidget(lineEdit,1,4);
      mainBox->addWidget(pred, 3,0);
      mainBox->addWidget(fromfileButton,4,0);
      mainBox->addWidget(lineEdit2,4,1);
      mainBox->addWidget(fileButton,5,0);
      mainBox->addWidget(lineEdit3,5,1);



     cent_widget->setLayout(mainBox);
     setCentralWidget(cent_widget);
     startString = " ";
     connect(table, SIGNAL(cellPressed(int,int)), this, SLOT(Saver(int,int)));
     connect(table, SIGNAL(cellChanged(int,int)), this, SLOT(Checked(int,int)));
  }

void View::createButtonClicked(){
    table->insertRow(table->rowCount());

    QDateEdit* date = new QDateEdit(QDate::currentDate() );
    date->setMinimumDate( QDate::fromString("1901.01.01", "yyyy.MM.dd"));
    date->setMaximumDate( QDate::currentDate());

    table->setCellWidget(table->rowCount()-1, 2, date);
    QTableWidgetItem* tmpItem = new QTableWidgetItem(QDate::currentDate().toString("yyyy.MM.dd"));
    table->setItem(table->rowCount()-1,2 , tmpItem);
    connect(table->cellWidget(table->rowCount()-1, 2), SIGNAL(dateChanged(QDate)), this, SLOT(setTextSlot(QDate)));
}

void View::deleteButtonClicked()
{
   auto selectedlist =  table->selectionModel()->selectedRows();
   while (!selectedlist.empty())
    {
        table->removeRow(selectedlist.at(0).row());
        selectedlist = table->selectionModel()->selectedRows();

   }
}

void View::setTextSlot(const QDate& date)
{
    table->currentItem()->setText(date.toString("yyyy.MM.dd"));
}

bool View::Name(QString &name)
{
    name = name.trimmed();
    QRegExp name_validator ("^[A-Za-zА-Яа-яЁё]+[- ]?[A-Za-zА-Яа-яЁё]+[- ]?[A-Za-zА-Яа-яЁё]*$");
    return name_validator.exactMatch(name);
}


bool View::Phone(QString &phone)
{
    phone = phone.trimmed();
    QRegExp phone_validator ("^(\\+\\d{1,3}\\(\\d{1,4}\\)\\d{1,4}-\\d{1,9}[,]?)+$");
    return phone_validator.exactMatch(phone);
}

bool View::Email(QString &email)
{
    email = email.trimmed();
    QRegExp email_validator ("^[A-Za-z0-9._]+[@][A-Za-z0-9]+\\.[A-Za-z]{2,}$");
    return email_validator.exactMatch(email);
}

void View::Saver(int row, int col)
{
    if (col == 2 or col == 1) return;
    if(table->item(row, col)!=nullptr) startString = table->item(row, col)->text();
}

void View::Checked(int i, int j)
{
    if ((j == 2) or (j == 1)) return;
        QString texttoCheck = table->item(i,j)->text();
        if (texttoCheck == " ") return;
        bool result = false;
        if(j==0) result = Name(texttoCheck);
        if(j==3) result = Email(texttoCheck);
        if(j==4) result = Phone(texttoCheck);
        if(!result)  {table->item(i,j)->setText(startString);
        QMessageBox warn;
        warn.setWindowTitle("Ошибка!");
        warn.setText("Неправильно введено значение! Было автоматически возвращено предыдущее значение!");
        warn.exec();}
}

void View::searchButtonClicked()
{
    QString texttoFind = lineEdit->text().toLower();
    table->clearSelection();
    for (int i= 0; i<table->rowCount(); i++ )
    {
        for (int j= 0; j<table->columnCount(); j++ )
        {
              if (table->item(i, j) == 0) continue;
              QString val = table->item(i, j)->text().toLower();
              if(j == 2) val = QDate::fromString(val, "yyyy.MM.dd").toString("dd.MM.yyyy");
              if (val.contains(texttoFind))
              {
                  table->selectionModel()->select(table->model()->index(i, j),
                                                                        QItemSelectionModel::Select | QItemSelectionModel::Toggle);
              }
        }
    }
}

void View::fileButtonClicked()
{
    QString textq = lineEdit3 ->text().toLower();
    QString Text_to_file = "C:/Users/79961/Documents/CourseWork/" + textq + ".txt";
    QFile file(Text_to_file);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "problem";
        return;
    }

    QTextStream out(&file);
    QString text = "";

    for (int i= 0; i<table->rowCount(); i++ )
    {
        if ((table->item(i,0)) and (table->item(i,4))){
            QString texttoCheck1 = table->item(i,0)->text();
            QString texttoCheck2 = table->item(i,4)->text();
            if(texttoCheck1 != "!!!" and texttoCheck2 != "!!!"){
            for (int j= 0; j<table->columnCount(); j++ )
            {
                 if (table->item(i, j) != 0)
                 {
                     text += table->item(i,j)->text();
                 }
                 else
                 {
                     text +=" ";
                 }
                 if (j!=table->columnCount()-1) text+='_';
            }
            text += "\n";
            }
        }
    }
    qDebug() << text;
    out << text;
    file.flush();
    file.close();
}

void View::fromfileButtonClicked()
{
    QString text = lineEdit2 ->text().toLower();
    QString Text_to_file = "C:/Users/79961/Documents/CourseWork/" + text + ".txt";
    QFile file(Text_to_file);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "problems";
        return;
    }
     QTextStream in(&file);
     table->setRowCount(0);
     table->setSortingEnabled(false);
     int i=0;
     while(!in.atEnd())
     {
         this->createButtonClicked();
         QString text = in.readLine();
         QStringList str_list = text.split(u'_');
         for (int j =0; j<table->columnCount(); j++ ) {
            QTableWidgetItem* tmp = new QTableWidgetItem(str_list.at(j));
            if(j ==2)
            {
                QDate date = QDate::fromString(QDate::fromString(str_list.at(j),"yyyy.MM.dd").toString("dd.MM.yyyy"),"dd.MM.yyyy");
                qDebug() <<  QDate::fromString("1901.01.01", "yyyy.MM.dd");
                QDateEdit* DateEdit = new QDateEdit(date);
                DateEdit->setMinimumDate( QDate::fromString("1901.01.01", "yyyy.MM.dd"));
                DateEdit->setMaximumDate( QDate::currentDate());
                table->setCellWidget(i,j, DateEdit);
                connect( table->cellWidget(i,j), SIGNAL(dateChanged(QDate)), this, SLOT(setTextSlot(QDate)));
            }
            table->setItem(i,j,tmp);
         }
         i++;
     }
     file.close();
     table->setSortingEnabled(true);
}
