#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include<QtWidgets>
#include<QMessageBox>
#include"tcpclient.h"
#include"mainwindow.h"

namespace Ui{
    class LoginWidget;
}
class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget*parent=nullptr);
    ~LoginWidget();
private slots:
    void on_btnLogin_clicked();
    void slotRecvData(QString msg);
private:
    Ui::LoginWidget *ui;
    TcpClient m_tcp;
    MainWindow *m_mainWin=nullptr;
    const quint16 PORT=8080;
    const QString SERVER_IP="192.168.15.118";
};

#endif // LOGINWIDGET_H
