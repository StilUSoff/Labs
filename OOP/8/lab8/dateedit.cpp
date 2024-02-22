#include "dateedit.h"

#include <QLineEdit>


DateEdit::DateEdit(QWidget *parent): QDateEdit(parent), m_dateTimeWasChanged(false) {
    connect(this, &QDateEdit::dateChanged, [this](){m_dateTimeWasChanged = true;});
}


void DateEdit::paintEvent(QPaintEvent *event) {
    if (!m_dateTimeWasChanged) {
        lineEdit()->setText("");
    }
    QDateEdit::paintEvent(event);
}
