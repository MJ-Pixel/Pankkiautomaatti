#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling, true);
    //QApplication::setAttribute(Qt::AA_Use96Dpi, true);
    QApplication a(argc, argv);
    //QFont font = qApp->font();
    //font.setPixelSize(11);
    //qApp->setFont(font);
    MainWindow  w;
    w.showFullScreen();


    return a.exec();
}
