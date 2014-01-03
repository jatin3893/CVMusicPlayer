#ifndef GLMAINWINDOW_H
#define GLMAINWINDOW_H

#include <iostream>
#include "fmodcontroller.h"
#include <QGLWidget>
#include <QTimer>
#include <math.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QResizeEvent>
#include <SOIL/SOIL.h>

#define HOVER 0
#define NORMAL 1
#define CLICK 2

class GLMainWindow : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLMainWindow(QWidget *parent = 0);
    //Variables
    QTimer *timer;
    QPoint cursor1, cursor2;
    //GL Variables
    struct icon{
        QString name;
        GLuint logo[3];
        QPoint centre;
        float radius;
    };

    struct icon start;
    struct icon stop;
    struct icon increase;
    struct icon decrease;

    struct icon sound1;
    struct icon sound2;
    struct icon sound3;
    struct icon sound4;
    struct icon sound5;
    struct icon sound6;

    void paintGL();

    //Initialisation Fucntions
    void initializeGL();
    void initialScene();

    //Drawing Functions
    void glowLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat thickness, QColor color);
    void glowCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat thickness, QColor color, int startAngle, int endAngle);
    void drawFillCircle(QPoint center, GLfloat radius);
    void loadTextures();
    void setupScene();
    void drawTexture(GLuint texture, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
    bool isInsideCircle(QPoint point, struct icon circle);

    //Event Listeners
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);

signals:
    void errorSignal(QString errorMessage);
    void debugSignal(QString debugMessage);
    void newControls(int controller1, int controller2);

public slots:
    void debugSlot(QString message);
    void errorSlot(QString message);
    void repaint();
    void updateControls(QPoint marker1, QPoint marker2);
};

#endif // GLMAINWINDOW_H
