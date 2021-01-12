#include "mainwindow.h"

#include <QApplication>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QDebug>

#include "bridge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("fusion");
    MainWindow w;
    w.show();

    return a.exec();
}
