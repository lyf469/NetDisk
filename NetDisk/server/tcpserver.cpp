#include "tcpserver.h"
#include<QByteArray>
#include<QSqlQuery>
#include<QMessageBox>

TcpServer::TcpServer(QObject *parent)
    : QTcpServer(parent)
{
    DBHelper::getInstance().openDB();
}

void TcpServer::startListen()
{
    if(listen(QHostAddress::Any,8080))
    {
        qDebug()<<"服务端启动成功，端口8080";
    }
    else
    {
        qDebug()<<"启动失败:"<<errorString();
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    QTcpSocket *socket=new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);
    clientList.append(socket);
    connect(socket,&QTcpSocket::readyRead,this,&TcpServer::recvMsg);
    connect(socket,&QTcpSocket::disconnected,this,&TcpServer::clientDisconnect);
}

void TcpServer::recvMsg()
{
    QTcpSocket *socket=qobject_cast<QTcpSocket*>(sender());
    QString data=QString::fromUtf8(socket->readAll());
    qDebug()<<"收到"<<data;
    if(data.startsWith("login#"))
    {
        QStringList info=data.split("#");
        QString user=info[1];
        QString pwd=info[2];
        QString sql=QString("select * from user where username='%1' and password='%2'").arg(user,pwd);
        QSqlQuery res=DBHelper::getInstance().querySql(sql);
        if(res.next())
        {
            socket->write("ok");
            qDebug()<<"用户"<<user<<"登陆成功";
        }
        else
        {
            socket->write("fail");
            qDebug()<<"用户"<<user<<"登陆失败";
        }
    }
}

void TcpServer::clientDisconnect()
{
    QTcpSocket *s=qobject_cast<QTcpSocket*>(sender());
    clientList.removeOne(s);
    s->deleteLater();
}



