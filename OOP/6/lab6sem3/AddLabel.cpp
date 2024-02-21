#include <AddLabel.h>
AddLabel::AddLabel()
{
    this->setText("0");
}

AddLabel::AddLabel(const QString& text)
{
    this->setText(text);
}

void AddLabel::setValue(int n_text)
{
    this->setText(QString::number(n_text));
    emit valueChanged(n_text);
}
