#include "src/other/global.h"

WebViewForTabs::WebViewForTabs(QWidget *parent) :
    QWebView(parent)
{
}

void WebViewForTabs::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::MiddleButton)
    {
        QWebHitTestResult aHitTest=page()->mainFrame()->hitTestContent(event->pos());

        if (!aHitTest.linkUrl().isEmpty())
        {
            emit openNewTab(aHitTest.linkUrl().toString());
        }
    }
    else
    {
        QWebView::mousePressEvent(event);
    }
}
