#include "fmodcontroller.h"

FMODController::FMODController(QWidget *parent) :
    QWidget(parent)
{
    connect(this, SIGNAL(errorSignal(QString)), this, SLOT(errorSlot(QString)));
    connect(this, SIGNAL(debugSignal(QString)), this, SLOT(debugSlot(QString)));

    unsigned int version;

    FMOD_RESULT result;

    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        emit errorSignal("Error!  You are using an old version of FMOD " + QString::number(version) + ". This program requires " + QString::number(FMOD_VERSION) + ".\n");
    }

    result = system->setOutput(FMOD_OUTPUTTYPE_ALSA);
    ERRCHECK(result);

    result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);

    loadAudioFiles();
}

void FMODController::controller(int controller1, int controller2)
{
    FMOD_RESULT result;
    if(controllerState.controller1 != controller1 || controllerState.controller2 != controller2)
    {
        emit debugSignal(QString::number(controller1) + " " + QString::number(controller2));
        switch(controller1)
        {
        case SOUND1:
        {
            switch(controller2)
            {
            case START:
            {
                result = system->playSound(FMOD_CHANNEL_FREE, sound1, 0, &channel);
                ERRCHECK(result);
            }
                break;
            case STOP:
            {
                emit debugSignal(tr("STOP SOUND 1"));
            }
                break;
            case INCREASE:
            {
                emit debugSignal(tr("INCREASE SOUND 1"));
            }
                break;
            case DECREASE:
            {
                emit debugSignal(tr("DECREASE SOUND 1"));
            }
                break;
            default:
            {

            }
                break;
            }
        }
            break;
        case SOUND2:
        {
            switch(controller2)
            {
            case START:
            {
                result = system->playSound(FMOD_CHANNEL_FREE, sound2, 0, &channel);
                ERRCHECK(result);
            }
                break;
            case STOP:
            {
                emit debugSignal(tr("STOP SOUND 2"));
            }
                break;
            case INCREASE:
            {
                emit debugSignal(tr("INCREASE SOUND 2"));
            }
                break;
            case DECREASE:
            {
                emit debugSignal(tr("DECREASE SOUND 2"));
            }
                break;
            default:
            {

            }
                break;
            }
        }
            break;
        case SOUND3:
        {
            switch(controller2)
            {
            case START:
            {
                result = system->playSound(FMOD_CHANNEL_FREE, sound3, 0, &channel);
                ERRCHECK(result);
            }
                break;
            case STOP:
            {
                emit debugSignal(tr("STOP SOUND 3"));
            }
                break;
            case INCREASE:
            {
                emit debugSignal(tr("INCREASE SOUND 3"));
            }
                break;
            case DECREASE:
            {
                emit debugSignal(tr("DECREASE SOUND 3"));
            }
                break;
            default:
            {

            }
                break;
            }
        }
            break;
        case SOUND4:
        {
            switch(controller2)
            {
            case START:
            {
                result = system->playSound(FMOD_CHANNEL_FREE, sound4, 0, &channel);
                ERRCHECK(result);
            }
                break;
            case STOP:
            {
                emit debugSignal(tr("STOP SOUND 4"));
            }
                break;
            case INCREASE:
            {
                emit debugSignal(tr("INCREASE SOUND 4"));
            }
                break;
            case DECREASE:
            {
                emit debugSignal(tr("DECREASE SOUND 4"));
            }
                break;
            default:
            {

            }
                break;
            }
        }
            break;
        case SOUND5:
        {
            switch(controller2)
            {
            case START:
            {
                result = system->playSound(FMOD_CHANNEL_FREE, sound4, 0, &channel);
                ERRCHECK(result);
            }
                break;
            case STOP:
            {
                emit debugSignal(tr("STOP SOUND 5"));
            }
                break;
            case INCREASE:
            {
                emit debugSignal(tr("INCREASE SOUND 5"));
            }
                break;
            case DECREASE:
            {
                emit debugSignal(tr("DECREASE SOUND 5"));
            }
                break;
            default:
            {

            }
                break;
            }
        }
            break;
        case SOUND6:
        {
            switch(controller2)
            {
            case START:
            {
                result = system->playSound(FMOD_CHANNEL_FREE, sound4, 0, &channel);
                ERRCHECK(result);
            }
                break;
            case STOP:
            {
                emit debugSignal(tr("STOP SOUND 6"));
            }
                break;
            case INCREASE:
            {
                emit debugSignal(tr("INCREASE SOUND 6"));
            }
                break;
            case DECREASE:
            {
                emit debugSignal(tr("DECREASE SOUND 6"));
            }
                break;
            default:
            {

            }
                break;
            }
        }
            break;
        default:
        {
        }
            break;
        }

        controllerState.controller1 = controller1;
        controllerState.controller2 = controller2;
    }
}

void FMODController::loadAudioFiles()
{
    FMOD_RESULT result;

    result = system->createSound("audio/1.wav", FMOD_SOFTWARE, 0, &sound1);
    ERRCHECK(result);
    result = sound1->setMode(FMOD_LOOP_OFF);
    ERRCHECK(result);

    result = system->createSound("audio/2.wav", FMOD_SOFTWARE, 0, &sound2);
    ERRCHECK(result);
    result = sound2->setMode(FMOD_LOOP_OFF);
    ERRCHECK(result);

    result = system->createSound("audio/3.wav", FMOD_SOFTWARE, 0, &sound3);
    ERRCHECK(result);
    result = sound3->setMode(FMOD_LOOP_OFF);
    ERRCHECK(result);

    result = system->createSound("audio/8.wav", FMOD_SOFTWARE, 0, &sound4);
    ERRCHECK(result);
    result = sound4->setMode(FMOD_LOOP_OFF);
    ERRCHECK(result);
}

void FMODController::ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        emit errorSignal("FMOD Error! (" + QString::number(result) + ") " + FMOD_ErrorString(result) + "/n");
    }
}

void FMODController::debugSlot(QString message)
{
    std::cout << "Debug: " << message.toStdString() << std::endl;
}

void FMODController::errorSlot(QString message)
{
    std::cout << "Error: " << message.toStdString() << std::endl;
}
