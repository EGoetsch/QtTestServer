#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QApplication>
#include <QTcpServer>
#include <QTcpSocket>
#include <mainwindow.h>


class Server : public QWidget {
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr) : QWidget(parent) {
        server = new QTcpServer(this);
        connect(server, &QTcpServer::newConnection, this, &Server::newConnection);
        if (!server->listen(QHostAddress::Any, 1234)) {
            qDebug() << "Server could not start!";
        } else {
            qDebug() << "Server started!";
        }
    }

    void setWindow(MainWindow *w){ this->w = w;}

private slots:
    void newConnection() {
        QTcpSocket *socket = server->nextPendingConnection();
        connect(socket, &QTcpSocket::readyRead, this, &Server::readMessage);
        qDebug() << "New connection established!";
    }

    void readMessage() {
        QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
        if (socket) {
            QString message = QString::fromUtf8(socket->readAll()).trimmed();
            qDebug() << "Received message:" << message;
            if (message == "stop") {
                qDebug() << "Stopping server...";
                qApp->quit();
            }
            if (message == "hide") {
                qDebug() << "HIDE";
                w->hide();
            }
            if (message == "show") {
                qDebug() << "SHOW";
                w->show();
            }
        }
    }

private:
    QTcpServer *server;
    MainWindow *w;
};

#endif // SERVER_H
