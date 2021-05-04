#ifndef PARK_H
#define PARK_H

#include "imode.h"

class Park : public IMode
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Park();

    //double getTime() override;
    double getInputPos(uint8_t index) override;
    void reset() override;
    Eigen::Matrix<double, 2, 6>& sample() override;
private:
    const double m_parkPosition;
    double m_heave;
};

#endif // PARK_H
