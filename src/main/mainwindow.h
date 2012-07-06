#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

struct SUndoUrl
{
    QString url;
    int index;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Ui::MainWindow *ui;
    QList<SUndoUrl> mUndoUrls;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateTabsStyle();

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);

public slots:
    void addTab(QString aUrl);

private slots:
    void tabUrlChanged(const QUrl &aUrl);
    void tabTitleChanged(const QString &aTitle);
    void tabIconChanged();

    void on_mainTabWidget_tabCloseRequested(int index);
    void on_actionClose_current_tab_triggered();
    void on_actionUndo_triggered();
};

#endif // MAINWINDOW_H
