#ifndef BROWSERTABBAR_H
#define BROWSERTABBAR_H

#include <QTabBar>

#include <QMouseEvent>

class BrowserTabBar : public QTabBar
{
    Q_OBJECT
public:
    explicit BrowserTabBar(QWidget *parent = 0);

    void moveTab(int from, int to);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void tabInserted(int index);
};

#endif // BROWSERTABBAR_H
