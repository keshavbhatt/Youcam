#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QNetworkAccessManager>
#include <QDebug>
#include <QNetworkReply>
#include <QWebSettings>
#include <QDesktopServices>
#include <QFile>
#include <QFileInfo>
#include <QBitmap>
#include <QMovie>
#include <QSettings>
#include <QCloseEvent>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{ if(this->isHidden()){
    ui->setupUi(this);
    QString appname =qApp->applicationName();
    this->setWindowTitle(appname+" - About");



    QString setting_path =  QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QString m_sSettingsFile2 = QApplication::applicationDirPath().left(1) + setting_path + "yocam.ini";
    QSettings settings(m_sSettingsFile2, QSettings::NativeFormat);
    bool twostate6=settings.value("usedark_theme","").toBool();

    if(twostate6){
        QMovie *movie = new QMovie(":images/jj.gif");
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setMovie(movie);
        movie->start();}
    else if(!twostate6){
        QMovie *movie = new QMovie(":images/jj.gif");
        this->setStyleSheet(QString("background-color:#302F2F;"));
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setMovie(movie);
        movie->start();}


    QNetworkAccessManager *m_netwManager = new QNetworkAccessManager(this);
    QObject::connect(m_netwManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_netwManagerFinished(QNetworkReply*)));
    QUrl url("https://twitter.com/keshavmail68/profile_image?size=original");
    QNetworkRequest request(url);
    //request.setRawHeader( "User-Agent" , "Mozilla Firefox" );
    m_netwManager->get(request);
}
else this->show();
}

void AboutDialog::slot_netwManagerFinished(QNetworkReply *reply)
{
    reply->deleteLater();

       if(reply->error() == QNetworkReply::NoError) {
           // Get the http status code
           int v = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
           if (v >= 200 && v < 300) // Success
           {
                //  got the final reply
               QString replyText = reply->readAll();
               qDebug()<<replyText<<"first reply text";
           }
           else if (v >= 300 && v < 400) // Redirection
           {
               // Get the redirection url
               QUrl newUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
               // Because the redirection url can be relative  we need to use the previous one to resolve it
               newUrl = reply->url().resolved(newUrl);
               qDebug()<<newUrl<<"redirected url";

               QNetworkAccessManager *manager = new QNetworkAccessManager();
               connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(netwManagerFinished(QNetworkReply*)));
               manager->get(QNetworkRequest(newUrl));
           }
       }
       else
       {
          QString setting_path =  QStandardPaths::writableLocation(QStandardPaths::DataLocation);
          QFileInfo checkFile(setting_path+"me.png");

           //if any error occurs load the image from offline storage
     if(checkFile.exists())
     {
         QPixmap pixmap;
         pixmap.load(setting_path+"me.png");
         pixmap=pixmap.scaledToWidth(200);
         ui->label->setPixmap(pixmap);
     }
     else if(!checkFile.exists())
     {    //set the image from qrc
         QPixmap pixmap(":/images/about.jpg");
         pixmap=pixmap.scaledToWidth(200);
         ui->label->setPixmap(pixmap);
           // show network error
           qDebug()<<  reply->errorString()<<"error string"; }
       }
       reply->manager()->deleteLater();
}

void AboutDialog::netwManagerFinished(QNetworkReply *reply){

    QString setting_path =  QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    QByteArray jpegData =reply->readAll();
    QPixmap pixmap;
  //  qDebug()<<jpegData.size();
    pixmap.loadFromData(jpegData);
    pixmap=pixmap.scaledToWidth(200);
    ui->label->setPixmap(pixmap);
    //save image for loading when user is offline
    pixmap.save(setting_path+"me.png", "PNG");
}
AboutDialog::~AboutDialog()
{
//    delete ui;
}

void AboutDialog::closeEvent(QCloseEvent *event){
    this->hide();
    event->ignore();
}




void AboutDialog::on_donate_clicked()
{
    QString url = "https://armybharti.in/donate.html";
    QDesktopServices::openUrl(url);
}

void AboutDialog::on_twitter_clicked()
{
   QString url = "https://twitter.com/keshavmail68";
           QDesktopServices::openUrl(url);
}



void AboutDialog::on_facebook_clicked()
{
   QString url = "https://facebook.com/keshav.bhatt.393";
           QDesktopServices::openUrl(url);
}

void AboutDialog::on_gmail_clicked()
{
    QString url = "mailto():keshavnrj@gmail.com";
    QDesktopServices::openUrl(url);

}
