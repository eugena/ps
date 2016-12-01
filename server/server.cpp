/****************************************************************************
**
** server.cpp
**
** Handling requests
**
****************************************************************************/

#include "server.h"
#include "calculator.h"
#include <string>

Server::Server(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect (server, SIGNAL(newConnection()), this, SLOT(newConnection()));
    if (!server->listen(QHostAddress::Any, 12345)) {
        qDebug() << "Server could not started.";
    } else {
        qDebug() << "Server has started.";
    }
}

Server::~Server() {
    server->close();
}

void Server::newConnection() {
    QTcpSocket *socket = server->nextPendingConnection();

    connect (socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect (socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "New client has connected";
}

void Server::disconnected() {
    qDebug() << "Client disconnected";
}

void Server::readyRead() {
    QString statement;
    Calculator *calculator = new Calculator;
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    int result;

    statement = socket->readAll();
    qDebug() << "Reading data...";
    qDebug() << "New statement:" << statement;
    if (calculator->checkStatement(statement)) {
        qDebug() << "Calculating...";
        result = calculator->getResult(statement);
        qDebug() << statement << "=" << result;
        socket->write(QString::number(result).toLocal8Bit());
    } else {
        qDebug() << "Incorrect statement";
        socket->write(NULL);
    }
}
