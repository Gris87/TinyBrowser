#include "webpagefortab.h"

WebPageForTab::WebPageForTab(QObject *parent) :
    QWebPage(parent)
{
}

QString WebPageForTab::userAgentForUrl(const QUrl & /*url*/) const
{
    return "Mozilla/5.0 (Windows NT 5.1) AppleWebKit/537.4 (KHTML, like Gecko) Chrome/22.0.1229.94 Safari/537.4";
}
