#ifndef IMODE_H
#define IMODE_H

#include <QObject>
#include <QDebug>

#include <Eigen/Dense>

#define PI 3.14159265358979323846

class IMode
{
public:
    virtual ~IMode() = default;

    //virtual double getTime() = 0;
    virtual double getInputPos(uint8_t index) = 0;
    virtual void reset() = 0;
    virtual Eigen::Matrix<double, 2, 6>& sample() = 0;

protected:
    enum PosVel { POS = 0, VEL = 1 };

    Eigen::Matrix<double, 2, 6> m_dof;
    double m_time;
};


#endif // IMODE_H
