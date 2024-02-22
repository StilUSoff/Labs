#include "WidgetCollection.h"


WidgetCollection::WidgetCollection(QWidget *parent): QMainWindow(parent) {
    CreateMenu();
    MakeDesign();
    ConnectButtons();
}


WidgetCollection::~WidgetCollection() {
}


void WidgetCollection::MakeDesign() {
    setFixedSize(800, 600);

    centralWidget->setFixedSize(800, 600);
    centralWidget->setStyleSheet("background-color: white;");

    topWidget->setStyleSheet("background-color: #FAEBD7;");
    bottomWidget->setStyleSheet("background-color: #000000;");

    createLabelButton->setStyleSheet("background-color: #FFFFFF;");
    createSliderButton->setStyleSheet("background-color: #FFFFFF;");
    createScrollbarButton->setStyleSheet("background-color: #FFFFFF;");
    createSpinBoxButton->setStyleSheet("background-color: #FFFFFF;");
}


void WidgetCollection::CreateMenu() {
    centralWidget = new QWidget(this);

    mainLayout = new QVBoxLayout(centralWidget);

    topWidget = new QWidget(this);
    mainLayout->addWidget(topWidget, 10);

    bottomWidget = new QWidget(this);
    mainLayout->addWidget(bottomWidget, 1);

    topLayout = new QGridLayout(topWidget);
    bottomLayout = new QHBoxLayout(bottomWidget);

    createLabelButton = new QPushButton("Label", bottomWidget);
    createSliderButton = new QPushButton("Slider", bottomWidget);
    createScrollbarButton = new QPushButton("Scrollbar", bottomWidget);
    createSpinBoxButton = new QPushButton("SpinBox", bottomWidget);

    bottomLayout->addWidget(createLabelButton);
    bottomLayout->addWidget(createSliderButton);
    bottomLayout->addWidget(createScrollbarButton);
    bottomLayout->addWidget(createSpinBoxButton);
}


void WidgetCollection::ConnectButtons() {
    connect(createLabelButton, &QPushButton::clicked, [=](){AddWidget(new QLabel(QString::number(value), this));});
    connect(createSliderButton, &QPushButton::clicked, [=](){AddWidget(new QSlider(Qt::Horizontal, topWidget));});
    connect(createScrollbarButton, &QPushButton::clicked, [=](){AddWidget(new QScrollBar(Qt::Horizontal, topWidget));});
    connect(createSpinBoxButton, &QPushButton::clicked, [=](){AddWidget(new QSpinBox(topWidget));});
}


//void WidgetCollection::CreateLabel() {
//    QLabel* widget = new QLabel(QString::number(value), topWidget);
////    widget->setStyleSheet("background-color: #FF7F50;");
////    qDebug("Create Label");
//    AddWidget(widget);
//}

//void WidgetCollection::CreateSlider(){
//    QSlider* widget = new QSlider(Qt::Horizontal, topWidget);

//    widget->setMinimum(0);
//    widget->setMaximum(100);
//    widget->setValue(value);

//    widget->setStyleSheet("background-color: #20B2AA;");
//    qDebug("Create Slider");
//    AddWidget(widget);
//}

//void WidgetCollection::CreateScrollbar(){
//    QScrollBar *widget = new QScrollBar(Qt::Horizontal, topWidget);

//    widget->setMinimum(0);
//    widget->setMaximum(100);
//    widget->setValue(value);

//    widget->setStyleSheet("background-color: #7CFC00;");
//    qDebug("Create ScrollBar");
//    AddWidget(widget);
//}

//void WidgetCollection::CreateSpinBox(){
//    QSpinBox* widget = new QSpinBox(topWidget);

//    widget->setMinimum(0);
//    widget->setMaximum(100);
//    widget->setValue(value);

//    widget->setStyleSheet("background-color: #BA55D3;");
//    qDebug("Create SpinBox");
//    AddWidget(widget);
//}


void WidgetCollection::AddWidget(QWidget* widget) {
    if (widget->metaObject()->className() == QString("QLabel")) {
        QLabel* label = qobject_cast<QLabel*>(widget);
        label->setStyleSheet("background-color: #FF7F50;");
    }

    else if (widget->metaObject()->className() == QString("QSlider")) {
        QSlider* slider = qobject_cast<QSlider*>(widget);
        slider->setMinimum(0);
        slider->setMaximum(100);
        slider->setValue(value);
        slider->setStyleSheet("background-color: #20B2AA;");
        connect(slider, &QSlider::valueChanged, [=](int value) {ChangeValue(slider, value);});
    }

    else if (widget->metaObject()->className() == QString("QScrollBar")) {
        QScrollBar* bar = qobject_cast<QScrollBar*>(widget);
        bar->setMinimum(0);
        bar->setMaximum(100);
        bar->setValue(value);
        bar->setStyleSheet("background-color: #7CFC00;");
        connect(bar, &QScrollBar::valueChanged, [=](int value) {ChangeValue(bar, value);});
    }

    else if (widget->metaObject()->className() == QString("QSpinBox")) {
        QSpinBox* box = qobject_cast<QSpinBox*>(widget);
        box->setMinimum(0);
        box->setMaximum(100);
        box->setValue(value);
        box->setStyleSheet("background-color: #BA55D3;");
        connect(box, &QSpinBox::valueChanged, [=](int value) {ChangeValue(box, value);});
    };

    if (column == 4) {row++; column = 0;}
    else column++;

    topLayout->addWidget(widget, row, column);
    widgets.append(widget);
}


void WidgetCollection::ChangeValue(QWidget* triggerWidget, int v) {
    value = v;

    for (int i = 0; i < widgets.size(); i++) {
        QWidget* widget = widgets[i];

        if (widget != triggerWidget) {
            qDebug() << widgets[i]->metaObject()->className();

            if (widget->metaObject()->className() == QString("QLabel")) {
                QLabel* label = qobject_cast<QLabel*>(widget);
                label->setText(QString::number(value));
            }

            else if (widget->metaObject()->className() == QString("QSlider")) {
                QSlider* slider = qobject_cast<QSlider*>(widget);
                slider->setValue(value);
            }

            else if (widget->metaObject()->className() == QString("QScrollBar")) {
                QScrollBar* bar = qobject_cast<QScrollBar*>(widget);
                bar->setValue(value);
            }

            else if (widget->metaObject()->className() == QString("QSpinBox")) {
                QSpinBox* box = qobject_cast<QSpinBox*>(widget);
                box->setValue(value);
            }
        }
    };
}

