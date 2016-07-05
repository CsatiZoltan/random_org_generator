#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>

#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
        // Создаем объект менеджера
    manager = new QNetworkAccessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->spinBox->value()>=ui->spinBox_2->value()){
        ui->textEdit->setText("Чуточку внимательнее с промежутками");
        return;
    }
    QString str;//();
    str = "https://www.random.org/integers/?num=";
    str = str + QString::number(ui->spinBox_3->value());
    str+= "&min=";
    str+= QString::number(ui->spinBox->value());
    str+= "&max=";
    str+= QString::number(ui->spinBox_2->value());
    str+= "&col=1&base=10&format=plain&rnd=new";
    QUrl url(str);
    QNetworkRequest request(url);
    QNetworkReply* reply=  manager->get(request);
    ui->textEdit->setText("Загружаю...");
    connect( reply, SIGNAL(finished()), this, SLOT(replyFinished()) );
}

void MainWindow::replyFinished()
{
  QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());

  if (reply->error() == QNetworkReply::NoError)
  {
    QByteArray content = reply->readAll();
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    ui->textEdit->setPlainText(codec->toUnicode(content.data()) );
  }
  else
  {
    ui->textEdit->setPlainText(reply->errorString());
  }
  // разрешаем объекту-ответа "удалиться"
  reply->deleteLater();
}

