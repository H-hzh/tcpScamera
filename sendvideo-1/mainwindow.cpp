#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cameraThread *c = new cameraThread;
    QThread *t1= new QThread;
    c->moveToThread(t1);
    t1->start();

    tcpThread *c1 = new tcpThread;
    QThread *t2= new QThread;
    c1->moveToThread(t2);
    t2->start();
    //控制摄像头
    connect(ui->btn_start,&QPushButton::clicked,c,&cameraThread::startCamera);
    connect(ui->btn_close,&QPushButton::clicked,c,&cameraThread::closeCamera);

    //是否发送数据
    connect(ui->btn_send,&QPushButton::clicked,this,[=](){
        if("发送数据" == ui->btn_send->text())
        {
            isSend = true;
            ui->btn_send->setText("停止发送");
        }
        else if("停止发送" == ui->btn_send->text())
        {
            isSend = false;
            ui->btn_send->setText("发送数据");
        }
        //发送数据创建一个新的线程
        if(isSend)
            emit initialize();
        else
            emit  closeScoket();

    });
    //服务器连接断开
    connect(this,&MainWindow::initialize,c1,&tcpThread::init);
    connect(this,&MainWindow::closeScoket,c1,&tcpThread::closeSocket);
    //将预览画面显示到控件上
    connect(c,&cameraThread::sendImage,this,[=](QImage i){
        if(isSend)//如果服务器连接，发送数据
            connect(c,&cameraThread::sendImage,c1,&tcpThread::sendPix);
        ui->label->setPixmap(QPixmap::fromImage(i));
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}



