#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableFile->setColumnCount(3);
    QStringList headers={"文件名","文件大小","上传时间"};
    ui->tableFile->setHorizontalHeaderLabels(headers);
    ui->tableFile->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableFile->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(&m_tcp,&TcpClient::recvMsg,this,&MainWindow::slotRecvData);
    m_tcp.sendMsg("filelist");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_btnUpload_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,"选择要上传的文件");
    if(filePath.isEmpty())
        return;
    m_tcp.uploadFile(filePath);
    ui->statusbar->showMessage("正在上传文件...",2000);
}

void MainWindow::on_btnDownload_clicked()
{
    int row=ui->tableFile->currentRow();
    if(row<0)
    {
        QMessageBox::information(this,"提示","请先选中表格里的文件");
        return;
    }
    QString fileName=ui->tableFile->item(row,0)->text();
    m_tcp.sendMsg("download#"+fileName);
    ui->statusbar->showMessage("开始下载:"+fileName,2000);
}

void MainWindow::on_btnDelete_clicked()
{
    int row=ui->tableFile->currentRow();
    if(row<0)
    {
        QMessageBox::information(this,"提示","请先选中表格里的文件");
        return;
    }
    QString fileName=ui->tableFile->item(row,0)->text();
    m_tcp.sendMsg("delete#"+fileName);
    ui->statusbar->showMessage("已发送删除指令",2000);
}

void MainWindow::slotRecvData(QString msg)
{
    if(msg.startsWith("filelist#"))
    {
        refreshFileTable(msg);
    }
    else if(msg=="upload_ok")
    {
        ui->statusbar->showMessage("文件上传成功",3000);
        m_tcp.sendMsg("filelist");
    }
    else if(msg=="delete_ok")
    {
        ui->statusbar->showMessage("文件删除成功",3000);
        m_tcp.sendMsg("filelist");
    }
    else if(msg=="download_ok")
    {
        ui->statusbar->showMessage("文件下载成功",3000);
    }
}

void MainWindow::refreshFileTable(QString data)
{
    ui->tableFile->setRowCount(0);
    QString raw=data.remove("filelist#");
    QStringList list=raw.split("#");
    for(int i=0;i<list.size();i+=3)
    {
        ui->tableFile->insertRow(ui->tableFile->rowCount());
        int newRow=ui->tableFile->rowCount()-1;
        ui->tableFile->setItem(newRow,0,new QTableWidgetItem(list[i]));
        ui->tableFile->setItem(newRow,1,new QTableWidgetItem(list[i+1]));
        ui->tableFile->setItem(newRow,2,new QTableWidgetItem(list[i+2]));
    }
}



