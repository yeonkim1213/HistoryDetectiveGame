#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DialogLogic dl;
    MainWindow w(dl);
    w.hide();
    return a.exec();
}
