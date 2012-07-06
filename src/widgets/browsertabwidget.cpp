#include "src/other/global.h"

BrowserTabWidget::BrowserTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    BrowserTabBar* aTabBar=new BrowserTabBar(this);
    connect(aTabBar, SIGNAL(tabMoved(int,int)), this, SLOT(tabMoved(int,int)));
    setTabBar(aTabBar);

    QString dir=QApplication::applicationDirPath()+"/";

    QDir aDir(dir);
    aDir.mkdir("icons");

    QWebSettings::setIconDatabasePath(dir+"icons");

    QWebSettings* aSettings=QWebSettings::globalSettings();

    aSettings->setAttribute(QWebSettings::PluginsEnabled, true);
}

QTabBar* BrowserTabWidget::tabBar() const
{
    return QTabWidget::tabBar();
}

void BrowserTabWidget::tabMoved(int from, int to)
{
    if (from==count()-1)
    {
        tabBar()->moveTab(to, from);
    }
}
