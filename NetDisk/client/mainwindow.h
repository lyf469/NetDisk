#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"tcpclient.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void refreshFileList();

private slots:

    void on_btnUpload_clicked();

    void on_btnDownload_clicked();

    void on_btnDelete_clicked();

    void slotRecvData(QString msg);

private:
    void refreshFileTable(QString data);
    Ui::MainWindow *ui;
    TcpClient m_tcp;
    const quint16 PORT=8080;
    const QString SERVER_IP="192.168.15.118";

};
#endif // MAINWINDOW_H
