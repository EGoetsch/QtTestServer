#include "mainwindow.h"

#include <QApplication>

#include <QApplication>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include "Server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Server server;
    MainWindow w;
    w.show();
    return a.exec();
}




