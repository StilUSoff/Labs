#include <QRandomGenerator>
#include <view.h>
Widget::Widget(QWidget *parent) : QWidget(parent) //конструктор
{
    ObjectList={};
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,500,500);

    createButton = new QPushButton("Создать");
    createButton->setGeometry(0,500,500,100);
    deleteButton = new QPushButton("Удалить");
    deleteButton->setGeometry(0,600,500,100);

    main = new QGraphicsView(scene);
    main->resize(1000,1000);
    scene->addWidget(createButton);
    scene->addWidget(deleteButton);

    connect(createButton, SIGNAL(clicked()), this, SLOT(create_obj()));
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(delete_obj()));
    main->show();

};

Widget::~Widget() //деструктор
{
}

void Widget::create_obj() //создание объектов
{
    Collection *item = new Collection();
    item->setPos(250,200);
    ObjectList.append(item);
    scene->addItem(item);
    QObject::connect(ObjectList[ObjectList.size()-1], SIGNAL(needtoBeFirstLayer(Collection*, int&)),this,SLOT(layOnFirstLayer(Collection*,int&)));
    //связываем сигнал со слотом, для того, чтобы возвращать объекты на передний план
}

void Widget::delete_obj() //удаление объектов
{
    QList<Collection*>::iterator it = ObjectList.begin();
    while (it != ObjectList.end()){
        if ((*it)->m_k == 1){
            delete *it;
            it = ObjectList.erase(it);
        }
        else {++it;}
    }
}




void Widget::layOnFirstLayer(Collection *Item , int& m_k) //возвращение объектов на передний план
{
    QList<Collection*>::iterator it = ObjectList.begin();
    if (m_k==0)
    {
        while (it != ObjectList.end()){
            (*it)->m_k = 0;
            ++it;
       }
        m_k=1;
      scene->removeItem(Item);
      scene->addItem(Item);

    }

}
