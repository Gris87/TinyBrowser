#include "webviewfortabs.h"

#include <QDebug>

WebViewForTabs::WebViewForTabs(QWidget *parent) :
    QWebView(parent)
{
}

void WebViewForTabs::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::MiddleButton)
    {
        QWebFrame *aFrame=page()->frameAt(event->pos());

        if (aFrame)
        {
            emit openNewTab(aFrame->url().toString());
        }
    }
    else
    {
        QWebView::mousePressEvent(event);
    }
}
