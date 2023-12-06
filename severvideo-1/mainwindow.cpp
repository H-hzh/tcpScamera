#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    myServer *m1 = new myServer;
    QThread *t1 = new QThread;
    m1->moveToThread(t1);
    t1->start();

    connect(ui->pushButton,&QPushButton::clicked,m1,&myServer::init);
//    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
//        qDebug()<<"开始监听";
//    });
    connect(m1,&myServer::sendPix,this,[=](QImage image){
//        qDebug()<<"2";
        ui->label->setPixmap(QPixmap::fromImage(image));
    });
}
