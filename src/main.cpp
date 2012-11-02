#include <QtGui/QApplication>
#include "src/other/global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    dir=QApplication::applicationDirPath()+"/";

    cookieJar=new QNetworkCookieJar();

    mainwindow=new MainWindow;
    mainwindow->show();

    int res=a.exec();

    delete mainwindow;
    delete cookieJar;

    QWebSettings::clearIconDatabase();

    return res;
}
