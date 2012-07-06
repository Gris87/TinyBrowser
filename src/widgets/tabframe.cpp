#include "src/other/global.h"

TabFrame::TabFrame(QString aUrl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabFrame)
{
    ui->setupUi(this);

    ui->progressBar->setVisible(false);

    ui->progressBar->setStyleSheet(
                                   "QProgressBar { "
                                        "border: 1px solid gray;"
                                        "border-radius: 3px;"
                                        "background: white;"
                                        "padding: 1px;"
                                   "}\n"
                                   "QProgressBar::chunk { "
                                        "background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 #009900, stop: 1 #BBFFBB); "
                                   "}"
                                   );

    connect(ui->urlLineEdit, SIGNAL(enterPressed()), this, SLOT(on_goButton_clicked()));

    ui->urlLineEdit->setText(aUrl);
    on_goButton_clicked();
}

TabFrame::~TabFrame()
{
    delete ui;
}

void TabFrame::openUrl(const QString &aUrl)
{
    ui->urlLineEdit->setText(aUrl);
    on_goButton_clicked();
}

void TabFrame::on_goButton_clicked()
{
    QString aUrl=ui->urlLineEdit->text();

    if (!aUrl.startsWith("http://", Qt::CaseInsensitive))
    {
        aUrl.insert(0, "http://");
    }

    ui->webView->setUrl(aUrl);
}

void TabFrame::on_webView_urlChanged(const QUrl &aUrl)
{
    ui->urlLineEdit->setText(aUrl.toString());
}

void TabFrame::on_webView_loadStarted()
{
    ui->progressBar->setVisible(true);
}

void TabFrame::on_webView_loadProgress(int progress)
{
    ui->progressBar->setValue(progress);
}

void TabFrame::on_webView_loadFinished(bool good)
{
    ui->progressBar->setVisible(false);
}
