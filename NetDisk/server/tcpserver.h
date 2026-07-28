#ifndef TCPSERVER_H
#define TCPSERVER_H
#include<QTcpServer>
#include<QTcpSocket>
#include"common.h"

class TcpServer:public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent=nullptr);
    void startListen();
protected:
    void incomingConnection(qintptr socketDescriptor) override;
private slots:
    void recvMsg();
    void clientDisconnect();
private:
    QList<QTcpSocket*> clientList;
};

#endif // TCPSERVER_H
