#ifndef NEUTRAL_H
#define NEUTRAL_H

#include "imode.h"

class Neutral : public IMode
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Neutral();

    double getInputPos(uint8_t index) override;
    void reset() override;
    Eigen::Matrix<double, 2, 6>& sample() override;

private:
    const double m_neutralPosition;
};

#endif // NEUTRAL_H
