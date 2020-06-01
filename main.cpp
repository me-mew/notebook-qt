#include "mainwindow.h"
#include "contacts.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mw;

    mw.show();

    return a.exec();
}
