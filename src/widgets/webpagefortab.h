#ifndef WEBPAGEFORTAB_H
#define WEBPAGEFORTAB_H

#include <QWebPage>

class WebPageForTab : public QWebPage
{
    Q_OBJECT
public:
    explicit WebPageForTab(QObject *parent = 0);

protected:
    QString userAgentForUrl(const QUrl &url) const;
};

#endif // WEBPAGEFORTAB_H
