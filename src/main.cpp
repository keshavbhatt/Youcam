#include "youcam.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("YouCam");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("org.keshavnrj.Youcam");
    QApplication::setOrganizationDomain("com.keshavnrj.youcam");


    YouCam w;
    w.show();

    return a.exec();
}
