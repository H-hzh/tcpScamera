#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QObject>

#include <QTcpSocket>
#include <QMutex>
#include <QMessageBox>
#include <QBuffer>
#include <QDebug>

#include <QtEndian>
class tcpThread : public QObject
{
    Q_OBJECT
public:
    explicit tcpThread(QObject *parent = nullptr);

    //连接初始化
    void init();
    void closeSocket();
    //发送到服务器
    void sendPix(QImage i);
signals:

private:
    QTcpSocket *m_tcpSocket;
    QMutex mutex;
};

#endif // TCPTHREAD_H
