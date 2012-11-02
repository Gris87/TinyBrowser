#ifndef GLOBAL_H
#define GLOBAL_H

#include <QDebug>

#include <QNetworkCookieJar>

#include "src/main/mainwindow.h"

#include "src/widgets/tabframe.h"
#include "src/widgets/urllineedit.h"
#include "src/widgets/webpagefortab.h"
#include "src/widgets/webviewfortabs.h"

extern MainWindow* mainwindow;

extern QNetworkCookieJar* cookieJar;

extern QString dir;

#endif // GLOBAL_H
