#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QVector>
#include <QString>
#include <QProcess>

#include "imode.h"
#include "rampneutral.h"
#include "neutral.h"
#include "oscillator.h"
#include "modeworker.h"
#include "park.h"
#include "joystick.h"

class Controller : public QObject
{
    // marker for MOC
    Q_OBJECT
    QThread workerThread;

    //Q_PROPERTY(double time READ getTime)
    Q_PROPERTY(double surgeOut READ getSurgeOut)
    Q_PROPERTY(double swayOut READ getSwayOut)
    Q_PROPERTY(double heaveOut READ getHeaveOut)
    Q_PROPERTY(double rollOut READ getRollOut)
    Q_PROPERTY(double pitchOut READ getPitchOut)
    Q_PROPERTY(double yawOut READ getYawOut)

    Q_PROPERTY(QVector<double> strokeRef READ getStrokeRef NOTIFY strokeRefChanged)
    Q_PROPERTY(QVector<double> strokeFb READ getStrokeFb NOTIFY strokeFbChanged)

    Q_PROPERTY(bool activated MEMBER m_activated NOTIFY activatedChanged)
    Q_PROPERTY(bool warning MEMBER m_warning NOTIFY warningChanged)
    Q_PROPERTY(bool canReadState MEMBER m_canReadState NOTIFY canReadStateChanged)

    Q_PROPERTY(int ampere READ getAmpere NOTIFY ampereChanged)

    Q_PROPERTY(QString runningProgram MEMBER m_runningProgram NOTIFY runningProgramChanged)

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    explicit Controller(Oscillator* oscillator, Joystick* joystick, QObject *parent = nullptr);
    ~Controller();

    double getSurgeOut() const;
    double getSwayOut() const;
    double getHeaveOut() const;
    double getRollOut() const;
    double getPitchOut() const;
    double getYawOut() const;

    uint8_t getAmpere() const;
    bool getCanReadState() const;

    QVector<double> getStrokeRef() const;
    QVector<double> getStrokeFb() const;

public slots:
    void setStrokeRef(const QVector<double>& newStrokeRef);
    void setStrokeFb(const QVector<double>& newStrokeFb);
    void setProgram(const QString& newProgram);
    void setWarningState(const bool& newWarningState);
    void setAmpere(const int& newAmpere);
    void setCanReadState(const bool& newCanReadState);

    void shutdown();

signals:
    void activatedChanged(const bool& run);
    void strokeRefChanged(const QVector<double>& newStrokeRef);
    void strokeFbChanged(const QVector<double>& newStrokeFb);
    void warningChanged(const bool& newWarningState);
    void workerProgramChanged(IMode* newWorkerProgram);
    void runningProgramChanged(const QString& newRunningProgram);
    void ampereChanged(const int& newAmpere);
    void canReadStateChanged(const bool& newCanReadState);

private:
    RampNeutral m_rampneutral;
    Park m_park;
    Oscillator* m_oscillator;
    Joystick* m_joystick;
    Neutral m_neutral;

    IMode* m_workerProgram;

    bool m_activated;
    bool m_warning;
    bool m_canReadState;

    QVector<double> m_strokeRef;
    QVector<double> m_strokeFb;

    uint8_t m_ampere;

    QString m_runningProgram;
};

#endif // CONTROLLER_H
