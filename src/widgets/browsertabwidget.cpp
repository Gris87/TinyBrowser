#include "browsertabwidget.h"

#include <QDebug>

BrowserTabWidget::BrowserTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    BrowserTabBar* aTabBar=new BrowserTabBar(this);

    connect(aTabBar, SIGNAL(tabMoved(int,int)), this, SLOT(tabMoved(int,int)));

    setTabBar(aTabBar);
}

void BrowserTabWidget::tabMoved(int from, int to)
{
    if (to==count()-1)
    {
        tabBar()->moveTab(to, from);
    }
    //qDebug()<<from<<to;
}
