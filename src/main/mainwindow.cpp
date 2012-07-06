#include "src/other/global.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addTab("yandex.ru");

    addAction(ui->actionClose_current_tab);
    addAction(ui->actionUndo);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setOptimalTabSize()
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
                                                                    "stop: 0 #EEEEFF, stop: 0.4 #D0D0FF,"
                                                                    "stop: 0.5 #C0C0FF, stop: 1.0 #EEEEFF); "
                                        "border-color: #9B9B9B; "
                                        "border-bottom-color: #C2C7CB "
                                     "}\n"
                                     "QTabBar::tab:last { "
                                        "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                                                                    "stop: 0 #FFC0C0, stop: 0.4 #FFB0B0,"
                                                                    "stop: 0.5 #EEA0A0, stop: 1.0 #FFC0C0); "
                                        "width: 16px; "
                                     "}\n"
                                     "QTabBar::tab:last:hover { "
                                        "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                                                                    "stop: 0 #FFDDDD, stop: 0.4 #FFCCCC,"
                                                                    "stop: 0.5 #EEBBBB, stop: 1.0 #FFDDDD)"
                                     "}\n"
                                     "QTabBar::tab:last:selected, QTabBar::tab:only-one { "
                                        "background: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1,"
                                                                    "stop: 0 #FFEEEE, stop: 0.4 #FFD0D0,"
                                                                    "stop: 0.5 #FFC0C0, stop: 1.0 #FFEEEE) "
                                     "}\n"
                                     "QTabBar::tab:!selected { "
                                        "margin-top: 2px "
                                     "}"
                                     );
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    setOptimalTabSize();

    QMainWindow::resizeEvent(event);
}

void MainWindow::showEvent(QShowEvent *event)
{
    setOptimalTabSize();

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

    setOptimalTabSize();
}

void MainWindow::tabUrlChanged(const QUrl &/*aUrl*/)
{
    int index=ui->mainTabWidget->indexOf((QWidget*)sender()->parent());

    if (index==ui->mainTabWidget->count()-1)
    {
        addTab("");
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
        mUndoUrls.append(((TabFrame*)ui->mainTabWidget->widget(index))->ui->urlLineEdit->text());

        delete ui->mainTabWidget->widget(index);

        if (index>0 && index==ui->mainTabWidget->count()-1)
        {
            ui->mainTabWidget->setCurrentIndex(index-1);
        }

        if (ui->mainTabWidget->count()==1)
        {
            ui->mainTabWidget->setTabText(0, "New tab");
        }

        setOptimalTabSize();
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
        addTab(mUndoUrls.takeLast());
    }
}
