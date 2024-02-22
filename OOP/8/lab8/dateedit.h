#pragma once

#include <QDateEdit>

class DateEdit : public QDateEdit
{
    Q_OBJECT
public:
    explicit DateEdit(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event) override;

signals:

public slots:

private:
    bool m_dateTimeWasChanged;
};
