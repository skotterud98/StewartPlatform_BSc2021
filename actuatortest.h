#ifndef ACTUATORTEST_H
#define ACTUATORTEST_H

#include "imode.h"

class ActuatorTest : public IMode
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    ActuatorTest();

    double getInputPos(uint8_t index) override;
    void reset() override;
    Eigen::Matrix<double, 2, 6>& sample() override;

private:

};

#endif // ACTUATORTEST_H
