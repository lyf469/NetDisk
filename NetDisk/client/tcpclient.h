#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include<QObject>
#include<QTcpSocket>


class TcpClient: public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent=nullptr);
    bool connectServer(const QString& ip,quint16 port,int waitMs=1000);
    void sendData(const QString& str);
    void closeSocket();
    void sendMsg(QString msg);
    void uploadFile(QString localFilePath);
signals:
    void recvMsg(QString data);
private:
    void onReadyRead();
private:
    QTcpSocket m_socket;
};

#endif // TCPCLIENT_H
