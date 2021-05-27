#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <QObject>
#include <QDebug>
#include <QString>

#include "imode.h"

#include <cmath>
#include <Eigen/Dense>


class Oscillator : public QObject, public IMode
{
    // Marker for MOC
    Q_OBJECT

    // Properties for the amplitude sliders in QML
    Q_PROPERTY(double surgeAmp READ getSurgeAmp WRITE setSurgeAmp NOTIFY surgeAmpChanged)
    Q_PROPERTY(double swayAmp READ getSwayAmp WRITE setSwayAmp NOTIFY swayAmpChanged)
    Q_PROPERTY(double heaveAmp READ getHeaveAmp WRITE setHeaveAmp NOTIFY heaveAmpChanged)
    Q_PROPERTY(double rollAmp READ getRollAmp WRITE setRollAmp NOTIFY rollAmpChanged)
    Q_PROPERTY(double pitchAmp READ getPitchAmp WRITE setPitchAmp NOTIFY pitchAmpChanged)
    Q_PROPERTY(double yawAmp READ getYawAmp WRITE setYawAmp NOTIFY yawAmpChanged)

    // Properties for the phase sliders in QML
    Q_PROPERTY(double surgePhase READ getSurgePhase WRITE setSurgePhase NOTIFY surgePhaseChanged)
    Q_PROPERTY(double swayPhase READ getSwayPhase WRITE setSwayPhase NOTIFY swayPhaseChanged)
    Q_PROPERTY(double heavePhase READ getHeavePhase WRITE setHeavePhase NOTIFY heavePhaseChanged)
    Q_PROPERTY(double rollPhase READ getRollPhase WRITE setRollPhase NOTIFY rollPhaseChanged)
    Q_PROPERTY(double pitchPhase READ getPitchPhase WRITE setPitchPhase NOTIFY pitchAmpChanged)
    Q_PROPERTY(double yawPhase READ getYawPhase WRITE setYawPhase NOTIFY yawPhaseChanged)

    // Properties for the frequency sliders in QML
    Q_PROPERTY(double surgeFreq READ getSurgeFreq WRITE setSurgeFreq NOTIFY surgeFreqChanged)
    Q_PROPERTY(double swayFreq READ getSwayFreq WRITE setSwayFreq NOTIFY swayFreqChanged)
    Q_PROPERTY(double heaveFreq READ getHeaveFreq WRITE setHeaveFreq NOTIFY heaveFreqChanged)
    Q_PROPERTY(double rollFreq READ getRollFreq WRITE setRollFreq NOTIFY rollFreqChanged)
    Q_PROPERTY(double pitchFreq READ getPitchFreq WRITE setPitchFreq NOTIFY pitchFreqChanged)
    Q_PROPERTY(double yawFreq READ getYawFreq WRITE setYawFreq NOTIFY yawFreqChanged)

    Q_PROPERTY(bool run READ getRun WRITE setRun NOTIFY runChanged)

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    explicit Oscillator(QObject *parent = nullptr);

    Eigen::Matrix<double, 2, 6>& sample() override;
    //double getTime() override;
    double getInputPos(uint8_t index) override;
    void reset() override;

    // Get-set functions for amplitude sliders
    double getSurgeAmp() const;
    void setSurgeAmp(const double& sliderVal);
    double getSwayAmp() const;
    void setSwayAmp(const double& sliderVal);
    double getHeaveAmp() const;
    void setHeaveAmp(const double& sliderVal);
    double getRollAmp() const;
    void setRollAmp(const double& sliderVal);
    double getPitchAmp() const;
    void setPitchAmp(const double& sliderVal);
    double getYawAmp() const;
    void setYawAmp(const double& sliderVal);

    // Get-set functions for phase sliders
    double getSurgePhase() const;
    void setSurgePhase(const double& sliderVal);
    double getSwayPhase() const;
    void setSwayPhase(const double& sliderVal);
    double getHeavePhase() const;
    void setHeavePhase(const double& sliderVal);
    double getRollPhase() const;
    void setRollPhase(const double& sliderVal);
    double getPitchPhase() const;
    void setPitchPhase(const double& sliderVal);
    double getYawPhase() const;
    void setYawPhase(const double& sliderVal);

    // Get-set functions for freq sliders
    double getSurgeFreq() const;
    void setSurgeFreq(const double& sliderVal);
    double getSwayFreq() const;
    void setSwayFreq(const double& sliderVal);
    double getHeaveFreq() const;
    void setHeaveFreq(const double& sliderVal);
    double getRollFreq() const;
    void setRollFreq(const double& sliderVal);
    double getPitchFreq() const;
    void setPitchFreq(const double& sliderVal);
    double getYawFreq() const;
    void setYawFreq(const double& sliderVal);

    bool getRun() const;
    void setRun(const bool& switchState);

public slots:
    void resetAmp();
    void resetPhase();
    void resetFreq();

signals:
    // Amplitude signals
    void surgeAmpChanged(const double& newSurgeAmp);
    void swayAmpChanged(const double& newSwayAmp);
    void heaveAmpChanged(const double& newHeaveAmp);
    void rollAmpChanged(const double& newRollAmp);
    void pitchAmpChanged(const double& newPitchAmp);
    void yawAmpChanged(const double& newYawAmp);

    // Phase signals
    void surgePhaseChanged(const double& newSurgePhase);
    void swayPhaseChanged(const double& newSwayPhase);
    void heavePhaseChanged(const double& newHeavePhase);
    void rollPhaseChanged(const double& newRollPhase);
    void pitchPhaseChanged(const double& newPitchPhase);
    void yawPhaseChanged(const double& newYawPhase);

    // Frequency signals
    void surgeFreqChanged(const double& newSurgeFreq);
    void swayFreqChanged(const double& newSwayFreq);
    void heaveFreqChanged(const double& newHeaveFreq);
    void rollFreqChanged(const double& newHeaveFreq);
    void pitchFreqChanged(const double& newPitchFreq);
    void yawFreqChanged(const double& newYawFreq);

    // Run switch signal
    void runChanged(const bool& newRunState);

private:
    enum SineParam { Amp = 0, Phase = 1, Freq = 2 };

    bool m_zeroAmpIn();

    double m_surge[3];
    double m_sway[3];
    double m_heave[3];
    double m_roll[3];
    double m_pitch[3];
    double m_yaw[3];

    bool m_run;

    const double m_heaveBias;
};

#endif // OSCILLATOR_H
