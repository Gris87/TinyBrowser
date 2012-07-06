#ifndef BROWSERTABWIDGET_H
#define BROWSERTABWIDGET_H

#include <QTabWidget>

#include "browsertabbar.h"

class BrowserTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit BrowserTabWidget(QWidget *parent = 0);

private slots:
    void tabMoved(int from, int to);
};

#endif // BROWSERTABWIDGET_H
