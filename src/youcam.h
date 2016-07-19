#ifndef YOUCAM_H
#define YOUCAM_H

#include <QMainWindow>
#include <QCamera>
#include <QMouseEvent>

namespace Ui {
class YouCam;
}

class YouCam : public QMainWindow
{
    Q_OBJECT

public:
    explicit YouCam(QWidget *parent = 0);
    ~YouCam();

protected:
        void mousePressEvent(QMouseEvent *evt)
        {
            oldPos = evt->globalPos();
        }

        void mouseMoveEvent(QMouseEvent *evt)
        {
            const QPoint delta = evt->globalPos() - oldPos;
            move(x()+delta.x(), y()+delta.y());
            oldPos = evt->globalPos();
        }

    private:
        QPoint oldPos;

private slots:
     void setStyle(QString fname);//set style of player from CSS file

     void enterEvent(QEvent * event);
     void leaveEvent(QEvent * event);


        void on_centralWidget_customContextMenuRequested(const QPoint &pos);

        void aboutDialog();


        void on_alwaysontop_clicked(bool checked);

        void on_fourBythree_clicked();

        void on_twoByfive_clicked();

        void on_trans_valueChanged(int value);

private:
    Ui::YouCam *ui;
     QCamera *camera;
};

#endif // YOUCAM_H
