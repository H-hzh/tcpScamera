#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#include <opencv2/videoio.hpp>
//#include <opencv2/highgui.hpp>

//using namespace cv;

#include "camerathread.h"
#include "tcpthread.h"
#include <QThread>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void initialize();
    void closeScoket();
private:
    Ui::MainWindow *ui;

    bool isSend = false;
//    Mat frame;
//    VideoCapture *cap;

};
#endif // MAINWINDOW_H
