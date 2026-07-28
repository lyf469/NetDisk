#include "tcpclient.h"
#include<QByteArray>
#include<QFile>

TcpClient::TcpClient(QObject *parent):QObject(parent)
{
    connect(&m_socket,&QTcpSocket::readyRead,this,&TcpClient::onReadyRead);
}

bool TcpClient::connectServer(const QString &ip, quint16 port, int waitMs)
{
    m_socket.connectToHost(ip,port);
    return m_socket.waitForConnected(waitMs);
}

void TcpClient::sendData(const QString &str)
{
    m_socket.write(str.toUtf8());
}

void TcpClient::closeSocket()
{
    if(m_socket.isOpen())
        m_socket.disconnectFromHost();
}

void TcpClient::sendMsg(QString msg)
{
    m_socket.write(msg.toUtf8());
}

void TcpClient::uploadFile(QString localFilePath)
{
    QFile file(localFilePath);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QString fileName=localFilePath.split("/").last();
    QByteArray fileData=file.readAll();
    file.close();
    QString cmd=QString("upload#%1#%2").arg(fileData.size());
    m_socket.write(cmd.toUtf8());
    m_socket.waitForBytesWritten(100);
    m_socket.write(fileData);
}

void TcpClient::onReadyRead()
{
    QByteArray buf=m_socket.readAll();
    QString res=QString::fromUtf8(buf);
    emit recvMsg(res);
}

