#ifndef BROWSERTABWIDGET_H
#define BROWSERTABWIDGET_H

#include <QTabWidget>

#include <QApplication>
#include <QWebSettings>
#include <QDir>

#include "browsertabbar.h"

class BrowserTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit BrowserTabWidget(QWidget *parent = 0);

    QTabBar* tabBar() const;

private slots:
    void tabMoved(int from, int to);
};

#endif // BROWSERTABWIDGET_H
