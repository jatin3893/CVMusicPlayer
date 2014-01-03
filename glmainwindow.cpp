#include "glmainwindow.h"

GLMainWindow::GLMainWindow(QWidget *parent) :
    QGLWidget(parent)
{
    connect(this, SIGNAL(errorSignal(QString)), this, SLOT(errorSlot(QString)));
    connect(this, SIGNAL(debugSignal(QString)), this, SLOT(debugSlot(QString)));

    timer = new QTimer();
    timer->start(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(repaint()));
}

void GLMainWindow::paintGL()
{
    QGLWidget::paintGL();
    setupScene();

    glColor3f(0, 1, 0);
    drawFillCircle(cursor1, 15);
    glColor3f(1, 0, 0);
    drawFillCircle(cursor2, 15);
}

void GLMainWindow::drawFillCircle(QPoint center, GLfloat radius)
{
    int i, noOfSides = 40;
    glBegin(GL_TRIANGLES);

    for(i = 0; i < noOfSides; i++)
    {
        glVertex2f(center.x() + radius * cos((i / noOfSides) * 360), center.y() + radius * sin((i / noOfSides) * 360));
        glVertex2f(center.x() + radius * cos(((i + 1) / noOfSides) * 360), center.y() + radius * sin(((i + 1) / noOfSides) * 360));
        glVertex2f(center.x(), center.y());
    }
    glEnd();
}

void GLMainWindow::repaint()
{
    QGLWidget::repaint();
}

void GLMainWindow::initializeGL()
{
    QGLWidget::initializeGL();
    glViewport(0, 0, this->size().width(), this->size().height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->size().width(), 0, this->size().height(), -1, 1);

    glClearColor(0, 0, 0, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    loadTextures();
}

void GLMainWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void GLMainWindow::mouseMoveEvent(QMouseEvent *event)
{

}

void GLMainWindow::mousePressEvent(QMouseEvent *event)
{

}

void GLMainWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

void GLMainWindow::keyPressEvent(QKeyEvent *event)
{

}

void GLMainWindow::keyReleaseEvent(QKeyEvent *event)
{

}

void GLMainWindow::resizeEvent(QResizeEvent *event)
{
    glViewport(0, 0, event->size().width(), event->size().height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, event->size().width(), 0, event->size().height(), -1, 1);
}

void GLMainWindow::glowLine(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat thickness, QColor color)
{
    GLfloat theta = atan((y2 - y1) / (x2 - x1));
    GLfloat y = thickness * cos(theta);
    GLfloat x = thickness * sin(theta);

    glBegin(GL_POLYGON);

    glColor4f(color.redF(), color.greenF(), color.blueF(), 1);
    glVertex2d(x2, y2);

    glColor4f(color.redF(), color.greenF(), color.blueF(), 0);
    glVertex2d(x2 - x, y2 + y);

    glColor4f(color.redF(), color.greenF(), color.blueF(), 0);
    glVertex2d(x1 - x, y1 + y);

    glColor4f(color.redF(), color.greenF(), color.blueF(), 1);
    glVertex2d(x1, y1);

    glColor4f(color.redF(), color.greenF(), color.blueF(), 0);
    glVertex2d(x1 + x, y1 - y);

    glColor4f(color.redF(), color.greenF(), color.blueF(), 0);
    glVertex2d(x2 + x, y2 - y);

    glEnd();
}

void GLMainWindow::glowCircle(GLfloat x, GLfloat y, GLfloat radius, GLfloat thickness, QColor color, int startAngle, int endAngle)
{
    while(endAngle < startAngle)
        endAngle += 360;

    GLfloat startAngleRad = startAngle * 3.142 / 180;
    float sectorAngle = endAngle - startAngle;

    int i, noOfSides = 40;

    for(i = 0; i < noOfSides; i+=1)
    {
        GLfloat theta1 =  ( ( ( i * sectorAngle ) / noOfSides ) * 3.142 ) / 180 + startAngleRad;
        GLfloat theta2 =  ( ( ( ( i + 1 ) * sectorAngle ) / noOfSides ) * 3.142 ) / 180 + startAngleRad;

        glBegin(GL_POLYGON);

        glColor4f(color.redF(), color.greenF(), color.blueF(), 1);
        glVertex2d(x + radius * cos(theta1), y + radius * sin(theta1));

        glColor4f(color.redF(), color.greenF(), color.blueF(), 0);
        glVertex2d(x + (radius - thickness/2) * cos(theta1), y + (radius - thickness/2) * sin(theta1));

        glColor4f(color.redF(), color.greenF(), color.blueF(), 0);
        glVertex2d(x + (radius - thickness/2) * cos(theta2), y + (radius - thickness/2) * sin(theta2));

        glColor4f(color.redF(), color.greenF(), color.blueF(), 1);
        glVertex2d(x + radius * cos(theta2), y + radius * sin(theta2));

        glColor4f(color.redF(), color.greenF(), color.blueF(), 0);
        glVertex2d(x + (radius + thickness/2) * cos(theta2), y + (radius + thickness/2) * sin(theta2));

        glColor4f(color.redF(), color.greenF(), color.blueF(), 0);
        glVertex2d(x + (radius + thickness/2) * cos(theta1), y +  (radius + thickness/2) * sin(theta1));

        glEnd();
    }
}

void GLMainWindow::loadTextures()
{
    void validateTexture(GLuint texture);

    start.logo[NORMAL] = SOIL_load_OGL_texture("icons/playNormal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(start.logo[NORMAL]);

    stop.logo[NORMAL] = SOIL_load_OGL_texture("icons/stopNormal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(stop.logo[NORMAL]);

    increase.logo[NORMAL] = SOIL_load_OGL_texture("icons/increaseNormal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(increase.logo[NORMAL]);

    decrease.logo[NORMAL] = SOIL_load_OGL_texture("icons/decreaseNormal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(decrease.logo[NORMAL]);

    start.logo[HOVER] = SOIL_load_OGL_texture("icons/playHover.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(start.logo[HOVER]);

    stop.logo[HOVER] = SOIL_load_OGL_texture("icons/stopHover.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(stop.logo[HOVER]);

    increase.logo[HOVER] = SOIL_load_OGL_texture("icons/increaseHover.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(increase.logo[HOVER]);

    decrease.logo[HOVER] = SOIL_load_OGL_texture("icons/decreaseHover.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(decrease.logo[HOVER]);

    start.logo[CLICK] = SOIL_load_OGL_texture("icons/playClick.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(start.logo[CLICK]);

    stop.logo[CLICK] = SOIL_load_OGL_texture("icons/stopClick.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(stop.logo[CLICK]);

    increase.logo[CLICK] = SOIL_load_OGL_texture("icons/increaseClick.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(increase.logo[CLICK]);

    decrease.logo[CLICK] = SOIL_load_OGL_texture("icons/decreaseClick.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(decrease.logo[CLICK]);

    sound1.logo[CLICK] = SOIL_load_OGL_texture("icons/1Click.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound1.logo[CLICK]);
    sound1.logo[HOVER] = SOIL_load_OGL_texture("icons/1Hover.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound1.logo[HOVER]);
    sound1.logo[NORMAL] = SOIL_load_OGL_texture("icons/1Normal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound1.logo[NORMAL]);

    sound2.logo[CLICK] = SOIL_load_OGL_texture("icons/2Click.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound2.logo[CLICK]);
    sound2.logo[HOVER] = SOIL_load_OGL_texture("icons/2Hover.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound2.logo[HOVER]);
    sound2.logo[NORMAL] = SOIL_load_OGL_texture("icons/2Normal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound2.logo[NORMAL]);

    sound3.logo[CLICK] = SOIL_load_OGL_texture("icons/3Click.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound3.logo[CLICK]);
    sound3.logo[HOVER] = SOIL_load_OGL_texture("icons/3Hover.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound3.logo[HOVER]);
    sound3.logo[NORMAL] = SOIL_load_OGL_texture("icons/3Normal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound3.logo[NORMAL]);

    sound4.logo[CLICK] = SOIL_load_OGL_texture("icons/4Click.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound4.logo[CLICK]);
    sound4.logo[HOVER] = SOIL_load_OGL_texture("icons/4Hover.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound4.logo[HOVER]);
    sound4.logo[NORMAL] = SOIL_load_OGL_texture("icons/4Normal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound4.logo[NORMAL]);

    sound5.logo[CLICK] = SOIL_load_OGL_texture("icons/5Click.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound5.logo[CLICK]);
    sound5.logo[HOVER] = SOIL_load_OGL_texture("icons/5Hover.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound5.logo[HOVER]);
    sound5.logo[NORMAL] = SOIL_load_OGL_texture("icons/5Normal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound5.logo[NORMAL]);

    sound6.logo[CLICK] = SOIL_load_OGL_texture("icons/6Click.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound6.logo[CLICK]);
    sound6.logo[HOVER] = SOIL_load_OGL_texture("icons/6Hover.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound6.logo[HOVER]);
    sound6.logo[NORMAL] = SOIL_load_OGL_texture("icons/6Normal.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    validateTexture(sound6.logo[NORMAL]);

    int soundIconRadius = 45;
    int controlIconRadius = 50;
    QPoint soundIconCenter(240, 240);
    int soundIconSetRadius = 150;
    int soundIconCount = 6;
    GLfloat angleDiff = (360 / soundIconCount) * 3.142 / 180;

    //Based On Calculated Values

    increase.centre = QPoint(570, 420);
    increase.radius = controlIconRadius;
    increase.name = QString(tr("Increase"));

    start.centre = QPoint(570, 300);
    start.radius = controlIconRadius;
    start.name = QString(tr("Start"));

    stop.centre = QPoint(570, 180);
    stop.radius = controlIconRadius;
    stop.name = QString(tr("Stop"));

    decrease.centre = QPoint(570, 60);
    decrease.radius = controlIconRadius;
    decrease.name = QString(tr("Decrease"));

    sound1.name = QString(tr("Sound 1"));
    sound1.centre = QPoint(soundIconCenter.x() + soundIconSetRadius * cos(0 * angleDiff), soundIconCenter.y() + soundIconSetRadius * sin(0 * angleDiff));
    sound1.radius = soundIconRadius;

    sound2.name = QString(tr("Sound 2"));
    sound2.centre = QPoint(soundIconCenter.x() + soundIconSetRadius * cos(1 * angleDiff), soundIconCenter.y() + soundIconSetRadius * sin(1 * angleDiff));
    sound2.radius = soundIconRadius;

    sound3.name = QString(tr("Sound 3"));
    sound3.centre = QPoint(soundIconCenter.x() + soundIconSetRadius * cos(2 * angleDiff), soundIconCenter.y() + soundIconSetRadius * sin(2 * angleDiff));
    sound3.radius = soundIconRadius;

    sound4.name = QString(tr("Sound 4"));
    sound4.centre = QPoint(soundIconCenter.x() + soundIconSetRadius * cos(3 * angleDiff), soundIconCenter.y() + soundIconSetRadius * sin(3 * angleDiff));
    sound4.radius = soundIconRadius;

    sound5.name = QString(tr("Sound 5"));
    sound5.centre = QPoint(soundIconCenter.x() + soundIconSetRadius * cos(4 * angleDiff), soundIconCenter.y() + soundIconSetRadius * sin(4 * angleDiff));
    sound5.radius = soundIconRadius;

    sound6.name = QString(tr("Sound 6"));
    sound6.centre = QPoint(soundIconCenter.x() + soundIconSetRadius * cos(5 * angleDiff), soundIconCenter.y() + soundIconSetRadius * sin(5 * angleDiff));
    sound6.radius = soundIconRadius;
}

void validateTexture(GLuint texture)
{
    if(texture == 0)
    {
        std::cout << "Unable to load texture" << std::endl;
    }
}

void GLMainWindow::setupScene()
{
    glColor4f(1, 1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    drawTexture(increase.logo[NORMAL], increase.centre.x() - increase.radius,
                                          increase.centre.y() - increase.radius,
                                          increase.centre.x() + increase.radius,
                                          increase.centre.y() + increase.radius);

    drawTexture(start.logo[NORMAL]   , start.centre.x() - start.radius,
                                          start.centre.y() - start.radius,
                                          start.centre.x() + start.radius,
                                          start.centre.y() + start.radius);

    drawTexture(stop.logo[NORMAL]   , stop.centre.x() - stop.radius,
                                          stop.centre.y() - stop.radius,
                                          stop.centre.x() + stop.radius,
                                          stop.centre.y() + stop.radius);

    drawTexture(decrease.logo[NORMAL]   , decrease.centre.x() - decrease.radius,
                                          decrease.centre.y() - decrease.radius,
                                          decrease.centre.x() + decrease.radius,
                                          decrease.centre.y() + decrease.radius);

    drawTexture(sound1.logo[NORMAL]   , sound1.centre.x() - sound1.radius,
                                          sound1.centre.y() - sound1.radius,
                                          sound1.centre.x() + sound1.radius,
                                          sound1.centre.y() + sound1.radius);

    drawTexture(sound2.logo[NORMAL]   , sound2.centre.x() - sound2.radius,
                                          sound2.centre.y() - sound2.radius,
                                          sound2.centre.x() + sound2.radius,
                                          sound2.centre.y() + sound2.radius);

    drawTexture(sound3.logo[NORMAL]   , sound3.centre.x() - sound3.radius,
                                          sound3.centre.y() - sound3.radius,
                                          sound3.centre.x() + sound3.radius,
                                          sound3.centre.y() + sound3.radius);

    drawTexture(sound4.logo[NORMAL]   , sound4.centre.x() - sound4.radius,
                                          sound4.centre.y() - sound4.radius,
                                          sound4.centre.x() + sound4.radius,
                                          sound4.centre.y() + sound4.radius);

    drawTexture(sound5.logo[NORMAL]   , sound5.centre.x() - sound5.radius,
                                          sound5.centre.y() - sound5.radius,
                                          sound5.centre.x() + sound5.radius,
                                          sound5.centre.y() + sound5.radius);

    drawTexture(sound6.logo[NORMAL]   , sound6.centre.x() - sound6.radius,
                                          sound6.centre.y() - sound6.radius,
                                          sound6.centre.x() + sound6.radius,
                                          sound6.centre.y() + sound6.radius);

    glDisable(GL_TEXTURE_2D);
}

void GLMainWindow::drawTexture(GLuint texture, GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f(x1, y1);

    glTexCoord2f(1, 0);
    glVertex2f(x2, y1);

    glTexCoord2f(1, 1);
    glVertex2f(x2, y2);

    glTexCoord2f(0, 1);
    glVertex2f(x1, y2);

    glEnd();
}

bool GLMainWindow::isInsideCircle(QPoint point, struct icon circle)
{
    GLfloat dx = (point.x() - circle.centre.x());
    GLfloat dy = (point.y() - circle.centre.y());
    dx = dx * dx;
    dy = dy * dy;

    if((dx + dy) < circle.radius * circle.radius)
        return true;
    else
        return false;
}

void GLMainWindow::updateControls(QPoint marker1, QPoint marker2)
{
    int controller1 = -1, controller2 = -1;

    cursor1 = QPoint(marker1);
    cursor2 = QPoint(marker2);

    if(isInsideCircle(marker2, start))
    {
        controller2 = FMODController::START;
    }
    else if(isInsideCircle(marker2, stop))
    {
        controller2 = FMODController::STOP;
    }
    else if(isInsideCircle(marker2, increase))
    {
        controller2 = FMODController::INCREASE;
    }
    else if(isInsideCircle(marker2, decrease))
    {
        controller2 = FMODController::DECREASE;
    }
    //Improve code of isInsideCircle by calculating boundaries directly

    if(isInsideCircle(marker1, sound1))
    {
        controller1 = FMODController::SOUND1;
    }
    else if(isInsideCircle(marker1, sound2))
    {
        controller1 = FMODController::SOUND2;
    }
    else if(isInsideCircle(marker1, sound3))
    {
        controller1 = FMODController::SOUND3;
    }
    else if(isInsideCircle(marker1, sound4))
    {
        controller1 = FMODController::SOUND4;
    }
    else if(isInsideCircle(marker1, sound5))
    {
        controller1 = FMODController::SOUND5;
    }
    else if(isInsideCircle(marker1, sound6))
    {
        controller1 = FMODController::SOUND6;
    }
    emit newControls(controller1, controller2);
}

void GLMainWindow::debugSlot(QString message)
{
    std::cout << "Debug: " << message.toStdString() << std::endl;
}

void GLMainWindow::errorSlot(QString message)
{
    std::cout << "Error: " << message.toStdString() << std::endl;
}
