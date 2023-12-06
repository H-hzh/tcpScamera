#include "myserver.h"

myServer::myServer(QObject *parent)
    : QObject{parent},m_isHead(false)
{

}

void myServer::init()
{
    qDebug()<<"开始监听";
    m_server = new QTcpServer(this);
//    m_socket = new QTcpSocket;
    m_server->listen(QHostAddress::Any,8989);

    //初始化套接字对象
    connect(m_server,&QTcpServer::newConnection,this,[=](){
        m_socket = m_server->nextPendingConnection();
        //读数据
        connect(m_socket,&QTcpSocket::readyRead,this,&myServer::read);

        //检测到数据转为图片
        connect(this,&myServer::sendtcp,this,&myServer::sendtcpToimage);
    });

}

void myServer::read()
{
    qint64 l =  m_socket->bytesAvailable();
    //如果连包头大小都不够返回            //就保存起来
    // 如果包头没取就判断长度跟包头比
    if(!m_isHead)
    {
        if( l < sizeof(int))
        {
            return;
        }
        else
        {
            m_socket->read(str,sizeof(int));
            size = (int*)str;
            qDebug()<<"size = " <<*size;
            m_isHead = true;
        }
        // 取出包头大小跟 l比较  如果满足则取数据
        if( l - sizeof(int) >= *size)
        {
            QByteArray tem = m_socket->read(*size); //未判断返回值  也不知取没取成功
            QByteArray array = QByteArray::fromBase64(tem);
            emit sendtcp(array);
            m_isHead = false;
            return;
        }

    }
    else
    {
        if(l<*size)
        {
            // 如果不够真实数据则等待下一次进来判断
            return;
        }
        else
        {
            QByteArray tem = m_socket->read(*size);
            QByteArray array = QByteArray::fromBase64(tem);
            emit sendtcp(array);
            m_isHead = false;
            return;
        }
    }
}

void myServer::sendtcpToimage(QByteArray byte)
{
//    qDebug()<<byte;
    QImage image = QImage::fromData(byte);
//    static int i = 1;
//    QString file = "./image/" + QString::number(i) + ".jpg";
//    i++;
//    if(!image.save(file))
//        qDebug()<<"11111";
    if(image.isNull())
    {
        qDebug()<<"图像为空";
        return;
    }
    emit sendPix(image);
}
