#ifndef TABFRAME_H
#define TABFRAME_H

#include <QWidget>
#include "ui_tabframe.h"

#include <QUrl>

namespace Ui {
class TabFrame;
}

class TabFrame : public QWidget
{
    Q_OBJECT

public:
    Ui::TabFrame *ui;

    explicit TabFrame(QString aUrl, QWidget *parent = 0);
    ~TabFrame();

    void openUrl(const QString &aUrl);

private slots:
    void on_goButton_clicked();
    void on_webView_urlChanged(const QUrl &aUrl);
};

#endif // TABFRAME_H
