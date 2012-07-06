#ifndef WEBVIEWFORTABS_H
#define WEBVIEWFORTABS_H

#include <QWebView>

#include <QWebFrame>
#include <QMouseEvent>

class WebViewForTabs : public QWebView
{
    Q_OBJECT
public:
    explicit WebViewForTabs(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void openNewTab(const QString& aUrl);
};

#endif // WEBVIEWFORTABS_H
