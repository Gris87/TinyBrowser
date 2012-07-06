#include "src/other/global.h"

TabFrame::TabFrame(QString aUrl, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabFrame)
{
    ui->setupUi(this);

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
