#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // TODO: Please run mainwindow manually or
    // remove this file and start mainwindow automatically...
    mainwindow w;
        w.show();

    return a.exec();
}
