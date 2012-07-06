#include "browsertabwidget.h"

BrowserTabWidget::BrowserTabWidget(QWidget *parent) :
    QTabWidget(parent)
{
    BrowserTabBar* aTabBar=new BrowserTabBar(this);
    connect(aTabBar, SIGNAL(tabMoved(int,int)), this, SLOT(tabMoved(int,int)));
    setTabBar(aTabBar);

    QString dir=QApplication::applicationDirPath()+"/";

    QDir aDir(dir);
    aDir.mkdir("icons");
    aDir.mkdir("storage");
    aDir.mkdir("cache");

    QWebSettings::setIconDatabasePath(dir+"icons");
    QWebSettings::setOfflineStoragePath(dir+"storage");
    QWebSettings::setOfflineStorageDefaultQuota(1000000);
    QWebSettings::enablePersistentStorage(dir+"storage");
    QWebSettings::setOfflineWebApplicationCachePath(dir+"cache");
    QWebSettings::setOfflineWebApplicationCacheQuota(1000000);
    QWebSettings::setMaximumPagesInCache(10);

    QWebSettings* aSettings=QWebSettings::globalSettings();

    aSettings->setLocalStoragePath(dir+"storage");
}

QTabBar* BrowserTabWidget::tabBar() const
{
    return QTabWidget::tabBar();
}

void BrowserTabWidget::tabMoved(int from, int to)
{
}
