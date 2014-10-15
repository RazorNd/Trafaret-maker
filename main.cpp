#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("ТРАФАРЕТ maker");
    MainWindow w;
    w.show();

    return a.exec();
}
