#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    /*To be changed later depending on added methods for marker identification.*/
    markerIdentificationMethod = HSV_VALUE;

    initialiseGUI();
    initialiseFMOD();
    initialiseConnections();
    initialiseCV();
}

void MainWindow::initialiseConnections()
{
    connect(this, SIGNAL(nextFrame(cv::Mat)), this, SLOT(updateImageWidget(cv::Mat)));
    connect(this, SIGNAL(cameraWorking()), this, SLOT(startCapturing()));
    connect(this, SIGNAL(debugSignal(QString)), this, SLOT(debugSlot(QString)));
    connect(this, SIGNAL(errorSignal(QString)), this, SLOT(errorSlot(QString)));
    connect(this, SIGNAL(nextFrame(cv::Mat)), this, SLOT(updateMarkerPosition(cv::Mat)));
    connect(this, SIGNAL(newMarkerPosition(QPoint,QPoint)), this, SLOT(calculateGestures(QPoint,QPoint)));
    connect(this, SIGNAL(markerPosition(QPoint)), this, SLOT(respondToMarker(QPoint)));
    connect(this, SIGNAL(newMarkerPosition(QPoint,QPoint)), glMainWindow, SLOT(updateControls(QPoint,QPoint)));
    connect(glMainWindow, SIGNAL(newControls(int,int)), fmodController, SLOT(controller(int,int)));
}

void MainWindow::initialiseCV()
{
    cap = new cv::VideoCapture(0);
    if(!cap->isOpened())
    {
        emit errorSignal("Video Camera Cannot Be Opened. \n ***From void MainWindow::initialiseCV() ***");
    }
    else
    {
        emit cameraWorking();
    }
}

void MainWindow::startCapturing()
{
    Mat temp, temp2;
    while(true)
    {
        *cap >> temp;
        cv::flip(temp, temp2, 1);
        emit nextFrame(temp2);
        waitKey(30);
    }
    return;
}

void MainWindow::initialiseGUI()
{
    this->setWindowTitle("Music Creator!");

    imageWidget = new CvImageWidget();
    layout = new QHBoxLayout();
    frameWidget = new QFrame(this);
    glMainWindow = new GLMainWindow(this);
    glMainWindow->setFixedSize(640, 480);

    layout->addWidget(imageWidget);
    layout->addWidget(glMainWindow);

    frameWidget->setLayout(layout);
    this->setCentralWidget(frameWidget);
    this->show();
}

void MainWindow::updateImageWidget(cv::Mat frame)
{
    this->imageWidget->showImage(frame);
}

void MainWindow::calculateGestures(QPoint marker1, QPoint marker2)
{
    int controller1 = NONE1;
    int controller2 = NONE2;

    circle(frame, Point(int(marker1.x()), int(marker1.y())), 3, Scalar(0, 0, 255), -1, 8, 0);
    circle(frame, Point(int(marker2.x()), int(marker2.y())), 3, Scalar(0, 255, 0), -1, 8, 0);

    if(marker1.x() >= 0 && marker1.x() <= 240)
    {
        if(marker1.y() >= 0 && marker1.y() <= 240)
        {
            controller1 = QUAD1;
        }
        else if(marker1.y() >= 240 && marker1.y() <= 480)
        {
            controller1 = QUAD2;
        }
        else
        {
            controller1 = NONE1;
        }
    }
    else if(marker1.x() >= 240 && marker1.y() <= 480)
    {
        if(marker1.y() >= 0 && marker1.y() <= 240)
        {
            controller1 = QUAD3;
        }
        else if(marker1.y() >= 240 && marker1.y() <= 480)
        {
            controller1 = QUAD4;
        }
        else
        {
            controller1 = NONE1;
        }
    }
    else
    {
        controller1 = NONE1;
    }

    if(marker2.x() >= 480 && marker2.x() <= 640)
    {
        if(marker2.y() <= 120)
        {
            controller2 = STOP;
        }
        else if(marker2.y() <= 240)
        {
            controller2 = DECREASE;
        }
        else if(marker2.y() <= 360)
        {
            controller2 = INCREASE;
        }
        else if(marker2.y() <= 640)
        {
            controller2 = START;
        }
        else
        {
            controller1 = NONE2;
        }
    }
    else
    {
        controller1 = NONE2;
    }
    emit newControlSignal(controller1, controller2, marker1, marker2);
}

void MainWindow::updateMarkerPosition(cv::Mat frame)
{
    Mat hsvFrame;
    cv::cvtColor(frame, hsvFrame, CV_BGR2HSV);
    if(markerIdentificationMethod == HSV_VALUE)
    {
        Mat threshFrame1, threshFrame2;
        Mat kernel;
        int size=3;
        Moments mu;

        int ID1_lowerH = 117, ID1_lowerS = 148, ID1_lowerV = 000;
        int ID1_upperH = 128, ID1_upperS = 255, ID1_upperV = 255;

        inRange(hsvFrame, Scalar(ID1_lowerH, ID1_lowerS, ID1_lowerV), Scalar(ID1_upperH, ID1_upperS, ID1_upperV), threshFrame1);
        kernel = getStructuringElement(MORPH_CROSS, Size(2*size+1, 2*size+1), Point(size, size));
        erode(threshFrame1, threshFrame1, kernel);
        dilate(threshFrame1, threshFrame1, kernel);
        dilate(threshFrame1, threshFrame1, kernel);

        mu = moments(threshFrame1);
        QPoint marker1 = QPoint(mu.m10/mu.m00, 480 - mu.m01/mu.m00);

        int ID2_lowerH = 000, ID2_lowerS = 221, ID2_lowerV = 000;
        int ID2_upperH =  28, ID2_upperS = 255, ID2_upperV = 255;

        inRange(hsvFrame, Scalar(ID2_lowerH, ID2_lowerS, ID2_lowerV), Scalar(ID2_upperH, ID2_upperS, ID2_upperV), threshFrame2);
        mu = moments(threshFrame2);
        QPoint marker2 = QPoint(mu.m10/mu.m00, 480 - mu.m01/mu.m00);

        emit newMarkerPosition(marker1, marker2);//For indicating marker position on frame.
    }
}

void MainWindow::debugSlot(QString message)
{
    std::cout << "Debug: " << message.toStdString() << std::endl;
}

void MainWindow::errorSlot(QString message)
{
    std::cout << "Error: " << message.toStdString() << std::endl;
}

void MainWindow::respondToMarker(QPoint marker)
{
    //For Individual marker specific work to be done. A general function for both markers. Can be Separated,
}

void MainWindow::initialiseFMOD()
{
    fmodController = new FMODController();
}

