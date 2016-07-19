#include "youcam.h"
#include "ui_youcam.h"
#include "aboutdialog.h"
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QMenu>



YouCam::YouCam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::YouCam)
{
    ui->setupUi(this);
     this->setWindowFlags(Qt::FramelessWindowHint);

    ui->setupUi(this);
    setStyle(":style.qss");
            camera = new QCamera(QCameraInfo::defaultCamera());
            camera->setViewfinder(ui->viewfinder);
            camera->load();
            camera->start();

            ui->viewfinder->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
            ui->viewfinder->setAttribute(Qt::WA_Hover);
            ui->viewfinder->setMouseTracking(true);


            ui->trans->setLayoutDirection(Qt::RightToLeft);
            ui->trans->setMinimum(15);
            ui->trans->setValue(100);

            ui->options->setVisible(false);
            connect(ui->quit,SIGNAL(clicked(bool)),this,SLOT(close()));
            connect(ui->alwaysontop,SIGNAL(clicked(bool)),this,SLOT(on_alwaysontop_clicked(bool)));
            connect(ui->fourBythree,SIGNAL(clicked()),this,SLOT(on_fourBythree_clicked()));
            connect(ui->twoByfive,SIGNAL(clicked()),this,SLOT(on_twoByfive_clicked()));
            connect(ui->trans,SIGNAL(valueChanged(int)),this,SLOT(on_trans_valueChanged(int)));
            connect(ui->viewfinder,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(on_centralWidget_customContextMenuRequested(QPoint)));



}


//Loading qss and setting style from it--------------------------------
void YouCam::setStyle(QString fname)
{
    QFile styleSheet(fname); // load CSS file
    if (!styleSheet.open(QIODevice::ReadOnly)) {
        qWarning("Unable to open file");
        return;
    }
    qApp->setStyleSheet(styleSheet.readAll()); // set own style
    styleSheet.close(); //close the file
}
//Loading qss and setting style from it-------------------------------


YouCam::~YouCam()
{
    delete camera;
    delete ui;
}




void YouCam::on_centralWidget_customContextMenuRequested(const QPoint &pos)
{

    QMenu *menu=new QMenu(this);
    menu->setFont(QFont("Ubuntu", 9));
    menu->setStyleSheet("border:0px;margin:0px;padding:0px;");
//    menu->actions().at(1)->setFont(QFont("Ubuntu", 7));
    menu->addAction(QString("About"),this,SLOT(aboutDialog()));
    menu->popup(ui->viewfinder->mapToGlobal(pos));

}

void YouCam::aboutDialog(){
AboutDialog *a = new AboutDialog(this);
a->show();
}

void YouCam::enterEvent(QEvent * event)
{
  //  qDebug() << Q_FUNC_INFO << this->objectName();
    QWidget::enterEvent(event);
    ui->options->setVisible(true);

}

void YouCam::leaveEvent(QEvent * event)
{
  //  qDebug() << Q_FUNC_INFO << this->objectName();
    QWidget::leaveEvent(event);
    ui->options->setVisible(false);


}




void YouCam::on_alwaysontop_clicked(bool checked)
{
    Qt::WindowFlags flags = this->windowFlags();
        if (checked)
        {
            this->setWindowFlags(flags | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
            ui->alwaysontop->setText("On Top");
            this->show();
        }
        else
        {
            this->setWindowFlags(flags ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
            ui->alwaysontop->setText("Always on top");
            this->show();
        }
}

void YouCam::on_fourBythree_clicked()
{
    this->resize(400,280);
}

void YouCam::on_twoByfive_clicked()
{
    this->resize(200,150);
}

void YouCam::on_trans_valueChanged(int value)
{
ui->opacity->display(value);
    setWindowOpacity(qreal(value)/100);
}
