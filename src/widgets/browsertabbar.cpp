#include "src/other/global.h"

BrowserTabBar::BrowserTabBar(QWidget *parent) :
    QTabBar(parent)
{
    setElideMode(Qt::ElideRight);
}

void BrowserTabBar::mousePressEvent(QMouseEvent *event)
{
    if (event->button()==Qt::MiddleButton)
    {
        int index=tabAt(event->pos());

        if (index>=0)
        {
            emit tabCloseRequested(index);
        }
    }
    else
    {
        if (event->button()==Qt::LeftButton)
        {
            int index=tabAt(event->pos());

            setMovable(index<count()-1);
        }

        QTabBar::mousePressEvent(event);
    }
}

void BrowserTabBar::mouseReleaseEvent(QMouseEvent *event)
{
    setMovable(true);

    QTabBar::mouseReleaseEvent(event);
}

void BrowserTabBar::tabInserted(int index)
{
    if (index==count()-1)
    {
        tabButton(index, QTabBar::RightSide)->resize(0, 0);

        if (index>0)
        {
            tabButton(index-1, QTabBar::RightSide)->resize(16, 16);
        }
    }

    QTabBar::tabInserted(index);
}
