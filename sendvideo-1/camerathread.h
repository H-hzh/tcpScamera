#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QObject>

#include "head.h"
#include <QtEndian>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

#include <QImage>
#include <QMessageBox>
#include <QBuffer>
#include <QDebug>

#include <QtEndian>
class cameraThread : public QObject
{
    Q_OBJECT
public:
    explicit cameraThread(QObject *parent = nullptr);



    //控制摄像头
    void startCamera();
    void closeCamera();

signals:
    //发送到主界面显示
    void sendImage(QImage i);
private:
    Mat frame;
    VideoCapture cap;
    bool b = true;


};

#endif // CAMERATHREAD_H
