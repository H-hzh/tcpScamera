#include "tcpthread.h"

tcpThread::tcpThread(QObject *parent)
    : QObject{parent}
{

}

void tcpThread::init()
{
    //    mutex.unlock();
    m_tcpSocket = new QTcpSocket;
    m_tcpSocket->connectToHost(QHostAddress("127.0.0.1"),8989);
    //如果连接失败
    connect(m_tcpSocket,&QTcpSocket::errorOccurred,this,[=](){
        QMessageBox::information(nullptr,"提示","连接失败");
        return;
    });
    //    connect(m_tcpSocket,&QTcpSocket::connected,this,[=](){
    //        QMessageBox::information(nullptr,"提示","连接成功");
    //        return;
    //    });
}

void tcpThread::closeSocket()
{
    qDebug()<<"关闭";
    if(m_tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        m_tcpSocket->disconnectFromHost();
        return;
    }
    //    m_tcpSocket->waitForDisconnected();
    //    m_tcpSocket->disconnectFromHost();
    //    m_tcpSocket->deleteLater();

}

void tcpThread::sendPix(QImage i)
{
//    if(!m_tcpSocket->state() == QAbstractSocket::ConnectedState)
//    {
//        QMessageBox::information(nullptr,"提示","未连接到服务器");
//        return;
//    }
//    connect(m_tcpSocket,&QTcpSocket::disconnected,this,[](){
//        QMessageBox::warning(nullptr,"提示","连接断开");
//        return;
//    });
    QMutexLocker locker(&mutex);
    QByteArray ba;
    QBuffer buffer(&ba);
    if(!i.save(&buffer,"jpg"))
        return;
    QByteArray sendb=buffer.data();//发送的数据
    sendb=sendb.toBase64();
    int a = sendb.size();
    char *str=(char*)&a;


    //         把 str[0-4] 的值 放在 sendb里 一起发过去  不然
    //  m_tcpSocket->write(str,sizeof(int)); 发少就惨

    qDebug()<<"a = "<<a;
    qDebug()<<"sendb = "<<sendb.size();

    m_tcpSocket->write(str,sizeof(int));
    m_tcpSocket->flush();
    m_tcpSocket->waitForBytesWritten();

    int writeSize = 0;//实际发送的数据大小
    int yiSize = 0;//已发送的大小
    int  myAllsize=a; //总数据大小
    while(1)
    {
        writeSize = m_tcpSocket->write(sendb);
        m_tcpSocket->flush();
        m_tcpSocket->waitForBytesWritten();
        yiSize += writeSize;
        sendb.remove(0,writeSize);//删掉本次实际发送的数据的大小
        if(yiSize >= myAllsize)
            return;
    }
}
