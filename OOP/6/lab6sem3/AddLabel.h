#ifndef ADDLABEL_H
#define ADDLABEL_H

#include <QWidget>
#include <QLabel>

class AddLabel: public QLabel
{
    Q_OBJECT
public:
    AddLabel();
    AddLabel(const QString& text);
signals:
    void valueChanged(int n_text);
public slots:
    void setValue(int n_text);
};

#endif // ADDLABEL_H
