#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(&m_tcp,&TcpClient::recvMsg,this,&Dialog::slotRecvMsg);
    m_tcp.connectServer(SERVER_IP,PORT);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_btnLogin_clicked()
{
    QString user=ui->edit_user->text();
    QString pwd=ui->edit_pwd->text();
    if(user.isEmpty() || pwd.isEmpty())
    {
        QMessageBox::warning(this,"提示","账号密码不能为空");
        return;
    }
    m_tcp.sendMsg(QString("login#%1#%2").arg(user).arg(pwd));
}

void Dialog::slotRecvMsg(QString msg)
{
    if(msg=="ok")
    {
        m_mainWin=new MainWindow();
        m_mainWin->show();
        this->accept();
    }
    else
    {
        QMessageBox::critical(this,"登陆失败","账号或密码错误");
    }
}
