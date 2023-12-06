#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>


#include <QTcpServer>
#include <QTcpSocket>

#include <QImage>
#include <QtEndian>
class myServer : public QObject
{
    Q_OBJECT
public:
    explicit myServer(QObject *parent = nullptr);

    void init();



public slots:
    void read();
    //接收客户端发来的数据，转换成图片
    void sendtcpToimage(QByteArray byte);
signals:
    /***
    *接收客户端发来的数据
    */
    void sendtcp(QByteArray byte);

    //发送图片给主线程
    void sendPix(QImage image);
private:
    QTcpServer *m_server;
    QTcpSocket *m_socket;

//    qint64 l;//实际长度
//    QByteArray m_array;//实际数据
    bool m_isHead = false;
    int *size ;
    char str[5]={0};
//    char *str;
};

#endif // MYSERVER_H
