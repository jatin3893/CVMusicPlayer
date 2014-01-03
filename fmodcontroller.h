#ifndef FMODCONTROLLER_H
#define FMODCONTROLLER_H

#include <QWidget>
#include <iostream>
#include <QString>

#include <fmod/fmod.hpp>
#include <fmod/fmod_errors.h>

class FMODController : public QWidget
{
    Q_OBJECT
public:
    enum CONTROLLER1_STATES{
         NONE1 = 200, SOUND1, SOUND2, SOUND3, SOUND4, SOUND5, SOUND6
    };
    enum CONTROLLER2_STATES{
         NONE2 = 300, STOP, DECREASE, INCREASE, START
    };
    struct{
        int controller1;
        int controller2;
    }controllerState;

    explicit FMODController(QWidget *parent = 0);
    
    FMOD::System *system;
    FMOD::Sound *sound1, *sound2, *sound3, *sound4;
    FMOD::Channel *channel;
    void loadAudioFiles();
    void ERRCHECK(FMOD_RESULT result);

signals:
    void errorSignal(QString errorMessage);
    void debugSignal(QString debugMessage);

public slots:
    void debugSlot(QString message);
    void errorSlot(QString message);
    void controller(int controller1, int controller2);

};

#endif // FMODCONTROLLER_H
