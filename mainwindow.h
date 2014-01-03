#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "cvimagewidget.h"
#include <QHBoxLayout>

#include "glmainwindow.h"
#include "fmodcontroller.h"

#include <opencv/cv.h>
#include <opencv/highgui.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    enum IDENTIFICATION_MEHOD{
        NONE = 100, HSV_VALUE, HAAR
    };
    enum CONTROLLER1_STATES{
         NONE1 = 200, QUAD1, QUAD2, QUAD3, QUAD4, SOUND1, SOUND2, SOUND3, SOUND4, SOUND5, SOUND6
    };
    enum CONTROLLER2_STATES{
         NONE2 = 300, STOP, DECREASE, INCREASE, START
    };

    int markerIdentificationMethod;
    QHBoxLayout *layout;
    QFrame *frameWidget;

//  CV Variables
    CvImageWidget *imageWidget;
    cv::VideoCapture *cap;
    cv::Mat frame;

//  FMOD Varibales
    FMODController *fmodController;

//  QGL Variables
    GLMainWindow *glMainWindow;


    MainWindow(QWidget *parent = 0);
    void updateImageWidget();
    void initialiseGUI();
    void initialiseCV();
    void initialiseFMOD();
    void initialiseConnections();

signals:
    void nextFrame(cv::Mat frame);
    void cameraWorking(void);
    void errorSignal(QString errorMessage);
    void debugSignal(QString debugMessage);
    void newMarkerPosition(QPoint marker1, QPoint marker2);
    void markerPosition(QPoint marker);
    void newControlSignal(int, int, QPoint, QPoint);

public slots:
    void updateImageWidget(cv::Mat frame);
    void updateMarkerPosition(cv::Mat frame);
    void startCapturing();
    void debugSlot(QString message);
    void errorSlot(QString message);
    void calculateGestures(QPoint marker1, QPoint marker2);
    void respondToMarker(QPoint marker);

private:
};

#endif // MAINWINDOW_H
