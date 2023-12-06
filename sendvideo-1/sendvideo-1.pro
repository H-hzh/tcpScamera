QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += D:\qt5.12.0\opencv\opencv\build\install\include
LIBS += D:\qt5.12.0\opencv\opencv\build\install\x64\mingw\bin\libopencv_*.dll

SOURCES += \
    camerathread.cpp \
    main.cpp \
    mainwindow.cpp \
    tcpthread.cpp

HEADERS += \
    camerathread.h \
    head.h \
    mainwindow.h \
    tcpthread.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
