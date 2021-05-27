#ifndef RAMPNEUTRAL_H
#define RAMPNEUTRAL_H

#include "imode.h"

class RampNeutral : public IMode
{

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    RampNeutral();

    double getInputPos(uint8_t index) override;
    void reset() override;
    Eigen::Matrix<double, 2, 6>& sample() override;

private:
    const double m_neutralPosition;
    double m_heave;
};

#endif // RAMPNEUTRAL_H
