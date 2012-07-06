#ifndef URLLINEEDIT_H
#define URLLINEEDIT_H

#include <QLineEdit>

#include <QKeyEvent>

class UrlLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit UrlLineEdit(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *event);

signals:
    void enterPressed();
};

#endif // URLLINEEDIT_H
