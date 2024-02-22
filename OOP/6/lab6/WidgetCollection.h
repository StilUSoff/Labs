#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

#include <QLabel>
#include <QScrollBar>
#include <QSpinBox>
#include <QSlider>
#include <QDebug>


using namespace std;


class WidgetCollection : public QMainWindow
{
    Q_OBJECT

private:
    int value = 50;

    int row = 0;
    int column = -1;

    QList<QWidget*> widgets;

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;

    QWidget *topWidget;
    QGridLayout *topLayout;

    QWidget *bottomWidget;
    QHBoxLayout *bottomLayout;

    QPushButton *createLabelButton;
    QPushButton *createSliderButton;
    QPushButton *createScrollbarButton;
    QPushButton *createSpinBoxButton;

    void MakeDesign();
    void CreateMenu();
    void ConnectButtons();

public:
    WidgetCollection(QWidget *parent = nullptr);
    ~WidgetCollection();
    void AddWidget(QWidget* widget);
    void ChangeValue(QWidget* triggerWidget, int v);
};

