#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <QObject>

#include <cmath>

#include "imode.h"

class Joystick : public QObject, public IMode
{
    Q_OBJECT

    Q_PROPERTY(double joyX MEMBER m_joyX NOTIFY joyXChanged)
    Q_PROPERTY(double joyY MEMBER m_joyY NOTIFY joyYChanged)
    Q_PROPERTY(double response READ getResponse WRITE setResponse NOTIFY responseChanged)
    Q_PROPERTY(double range READ getRange WRITE setRange NOTIFY rangeChanged)
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    explicit Joystick(QObject *parent = nullptr);

    double getInputPos(uint8_t index) override;
    void reset() override;
    Eigen::Matrix<double, 2, 6>& sample() override;

    double getResponse() const;
    void setResponse(const double& newResponse);

    double getRange() const;
    void setRange(const double& newRange);

signals:
    void joyXChanged(const double& newX);
    void joyYChanged(const double& newY);
    void responseChanged(const double& newResponse);
    void rangeChanged(const double& newRange);

private:
    double m_joyX;
    double m_joyY;

    double m_roll;
    double m_pitch;

    double m_responseK;
    double m_maxAngle;

    const double neutralHeave;
};

#endif // JOYSTICK_H
