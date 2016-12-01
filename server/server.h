/****************************************************************************
**
** server.h
**
****************************************************************************/

#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);
    ~Server();

signals:

public slots:
    void newConnection();
    void disconnected();
    void readyRead();

private:
    QTcpServer *server;
};

#endif // SERVER_H
