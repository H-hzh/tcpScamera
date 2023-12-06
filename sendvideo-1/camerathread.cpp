#include "camerathread.h"

#include <QThread>

cameraThread::cameraThread(QObject *parent)
    : QObject{parent}
{

}


void cameraThread::startCamera()
{
    //    Mat frame;
    //    VideoCapture cap;
    cap.open(0,cv::CAP_ANY);//使用默认摄像头
    if(!cap.isOpened())
        return;
    while(b)
    {
        cap.read(frame);
        if (frame.empty())
            return;

//        QImage image = QImage(frame.data,frame.cols,frame.rows,frame.step,format);
        QImage image = QImage(frame.data, frame.cols, frame.rows, static_cast<int>(frame.step), QImage::Format_BGR888);
        emit sendImage(image);
    }

    // show live and wait for a key with timeout long enough to show images
    //    cv::imshow("Live", frame);
}

void cameraThread::closeCamera()
{
    qDebug()<<"关闭";
    cap.release();
}


