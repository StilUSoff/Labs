#include <WidgetCollection.h>
#include<AddLabel.h>

Collection::Collection(QWidget *parent)
    : QWidget(parent)
{
    WidgetList={};
    value = 0;
    mainBox = new QVBoxLayout(this);

    createButton = new QPushButton("Создать");
    deleteButton = new QPushButton("Удалить");

    mainBox->addWidget(createButton);
    mainBox->addWidget(deleteButton);

    connect(createButton, SIGNAL(clicked()), this, SLOT(create_obj()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(delete_obj()));
}

Collection::~Collection(){}

void Collection::create_obj()
{
    members Object = members(QRandomGenerator::global()->bounded(1,6));
    //QDial
    switch(Object)
    {
        case Qlabel:
    {
          AddLabel* Label = new AddLabel(QString::number(value));
          Label->setAlignment(Qt::AlignHCenter); //По умолчанию содержимое метки выравнивается по левому краю и центрируется по вертикали.
          WidgetList.append(Label);
          ConnectWidget();
          mainBox->addWidget(WidgetList.last(), WidgetList.size()+1);
          break;
    }
        case Qslider:
    {
        QSlider* tmp = new QSlider();
        tmp->setValue(value);
        WidgetList.append(tmp);
        ConnectWidget();
        mainBox->addWidget(WidgetList.last(), WidgetList.size()+1);
            break;
    }
        case Qscrollbar:
    {
        QScrollBar* tmp = new QScrollBar();
        tmp->setValue(value);
        WidgetList.append(tmp);
        ConnectWidget();
        mainBox->addWidget(WidgetList.last(), WidgetList.size()+1);
         break;
    }
        case Qspinbox:
    {
        QSpinBox* tmp = new QSpinBox();
        tmp->setValue(value);
        WidgetList.append(tmp);
        ConnectWidget();
        mainBox->addWidget(WidgetList.last(), WidgetList.size()+1);
            break;
    }
    case Qdial:
    {
      QDial* tmp = new QDial();
      tmp->setValue(value);
      WidgetList.append(tmp);
      ConnectWidget();
      mainBox->addWidget(WidgetList.last(), WidgetList.size()+1);
          break;

    }
    }
}


void Collection::delete_obj()
{
   if(!WidgetList.empty())
   {
      mainBox->removeWidget(WidgetList.last());
      delete WidgetList.last();
      WidgetList.pop_back();
   }
}


void Collection::setValue(int i)
{
    value = i;
    emit valueChanged(i);
}


void Collection::ConnectWidget()
{
    if(WidgetList.size()>0)
    {

        QList<QWidget*>::Iterator it;
        for (it = WidgetList.begin(); it!=WidgetList.end()-1; it++)
        {
            QObject::connect(WidgetList[WidgetList.size()-1], SIGNAL(valueChanged(int)),*it,SLOT(setValue(int)));
            if(!(*it)->inherits("QLabel"))
            {
                QObject::connect(*it, SIGNAL(valueChanged(int)),WidgetList[WidgetList.size()-1],SLOT(setValue(int)));
                QObject::connect(*it, SIGNAL(valueChanged(int)),this,SLOT(setValue(int)));
            }
         }
    }
}

