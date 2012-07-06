#include "src/other/global.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addTab("yandex.ru");
    addTab("");

    addAction(ui->actionClose_current_tab);
    addAction(ui->actionUndo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTabsStyle()
{
    int aTabWidth=(ui->mainTabWidget->width()/(ui->mainTabWidget->count()+1));

    if (aTabWidth>150)
    {
        aTabWidth=150;
    }
    else
    if (aTabWidth<8)
    {
        aTabWidth=8;
    }

    ui->mainTabWidget->setStyleSheet(
                                     "QTabWidget::pane { "
                                        "border-top: 2px solid #C2C7CB "
                                     "}\n"
                                     "QTabWidget::tab-bar { "
                                        "left: 4px "
                                     "}\n"
                                     "QTabBar::tab { "

                                        "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                                                                    "stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
                                                                    "stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); "
                                        "border: 2px solid #C4C4C3; "
                                        "border-bottom-color: #C2C7CB; "
                                        "border-top-left-radius: 4px; "
                                        "border-top-right-radius: 4px; "
                                        "width: "+QString::number(aTabWidth)+"px; "
                                        "padding: 2px"
                                     "}\n"
                                     "QTabBar::tab:hover { "
                                        "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                                                                    "stop: 0 #FAFAFA, stop: 0.4 #F4F4F4,"
                                                                    "stop: 0.5 #E7E7E7, stop: 1.0 #FAFAFA)"
                                     "}\n"
                                     "QTabBar::tab:selected { "
                                        "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                                                                    "stop: 0 #F4F4FF, stop: 0.4 #E0E0FF,"
                                                                    "stop: 0.5 #D0D0FF, stop: 1.0 #F4F4FF); "
                                        "border-color: #9B9B9B; "
                                        "border-bottom-color: #C2C7CB "
                                     "}\n"
                                     "QTabBar::tab:last { "
                                        "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                                                                    "stop: 0 #EE9090, stop: 0.4 #EE7070,"
                                                                    "stop: 0.5 #EE6060, stop: 1.0 #EE9090); "
                                        "width: 16px; "
                                     "}\n"
                                     "QTabBar::tab:last:hover { "
                                        "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                                                                    "stop: 0 #EEA0A0, stop: 0.4 #EEAAAA,"
                                                                    "stop: 0.5 #EE9999, stop: 1.0 #EEA0A0)"
                                     "}\n"
                                     "QTabBar::tab:last:selected, QTabBar::tab:only-one { "
                                        "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                                                                    "stop: 0 #FFC0C0, stop: 0.4 #FFB0B0,"
                                                                    "stop: 0.5 #EEA0A0, stop: 1.0 #FFC0C0) "
                                     "}\n"
                                     "QTabBar::tab:!selected { "
                                        "margin-top: 3px "
                                     "}"
                                     );
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    updateTabsStyle();

    QMainWindow::resizeEvent(event);
}

void MainWindow::showEvent(QShowEvent *event)
{
    updateTabsStyle();

    QMainWindow::showEvent(event);
}

void MainWindow::addTab(QString aUrl)
{
    TabFrame* aTab=new TabFrame(aUrl, this);

    connect(aTab->ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(tabUrlChanged(QUrl)));
    connect(aTab->ui->webView, SIGNAL(titleChanged(QString)), this, SLOT(tabTitleChanged(QString)));
    connect(aTab->ui->webView, SIGNAL(iconChanged()), this, SLOT(tabIconChanged()));
    connect(aTab->ui->webView, SIGNAL(openNewTab(QString)), this, SLOT(addTab(QString)));

    if (aUrl=="")
    {
        ui->mainTabWidget->addTab(aTab, "+");
    }
    else
    {
        ui->mainTabWidget->insertTab(ui->mainTabWidget->count()-1, aTab, aUrl);
    }

    updateTabsStyle();
}

void MainWindow::tabUrlChanged(const QUrl &aUrl)
{
    int index=ui->mainTabWidget->indexOf((QWidget*)sender()->parent());

    if (index>=0)
    {
        ui->mainTabWidget->setTabText(index, aUrl.toString());
        ui->mainTabWidget->setTabToolTip(index, "");
        ui->mainTabWidget->setTabIcon(index, QWebSettings::iconForUrl(aUrl));

        if (index==ui->mainTabWidget->count()-1)
        {
            addTab("");
        }
    }
}

void MainWindow::tabTitleChanged(const QString &aTitle)
{
    if (aTitle!="")
    {
        int index=ui->mainTabWidget->indexOf((QWidget*)sender()->parent());

        if (index>=0)
        {
            ui->mainTabWidget->setTabText(index, aTitle);
            ui->mainTabWidget->setTabToolTip(index, aTitle);
        }
    }
}

void MainWindow::tabIconChanged()
{
    int index=ui->mainTabWidget->indexOf((QWidget*)sender()->parent());

    if (index>=0)
    {
        ui->mainTabWidget->setTabIcon(index, ((QWebView*)(sender()))->icon());
    }
}

void MainWindow::on_mainTabWidget_tabCloseRequested(int index)
{
    if (index<ui->mainTabWidget->count()-1)
    {
        SUndoUrl aUndoUrl;
        aUndoUrl.url=((TabFrame*)ui->mainTabWidget->widget(index))->ui->urlLineEdit->text();
        aUndoUrl.index=index;
        mUndoUrls.append(aUndoUrl);

        delete ui->mainTabWidget->widget(index);

        if (index>0 && index==ui->mainTabWidget->count()-1)
        {
            ui->mainTabWidget->setCurrentIndex(index-1);
        }

        if (ui->mainTabWidget->count()==1)
        {
            ui->mainTabWidget->setTabText(0, "New tab");
        }

        updateTabsStyle();
    }
}

void MainWindow::on_actionClose_current_tab_triggered()
{
    on_mainTabWidget_tabCloseRequested(ui->mainTabWidget->currentIndex());
}

void MainWindow::on_actionUndo_triggered()
{
    if (mUndoUrls.length()>0)
    {
        if (ui->mainTabWidget->count()==1)
        {
            ui->mainTabWidget->setTabText(ui->mainTabWidget->count()-1, "+");
        }

        SUndoUrl aUndoUrl=mUndoUrls.takeLast();

        addTab(aUndoUrl.url);
        ui->mainTabWidget->tabBar()->moveTab(ui->mainTabWidget->count()-2, aUndoUrl.index);
        ui->mainTabWidget->setCurrentIndex(aUndoUrl.index);
    }
}
