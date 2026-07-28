#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"tcpclient.h"
#include"mainwindow.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_btnLogin_clicked();
    void slotRecvMsg(QString msg);

private:
    Ui::Dialog *ui;
    TcpClient m_tcp;
    const quint16 PORT=8080;
    const QString SERVER_IP="192.168.15.118";
    MainWindow *m_mainWin=nullptr;
};

#endif // DIALOG_H
