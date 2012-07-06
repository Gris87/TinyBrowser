#include "urllineedit.h"

UrlLineEdit::UrlLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void UrlLineEdit::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Return || event->key()==Qt::Key_Enter)
    {
        emit enterPressed();
    }

    QLineEdit::keyPressEvent(event);
}
