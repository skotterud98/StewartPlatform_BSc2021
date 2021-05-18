#include "actuatortest.h"

ActuatorTest::ActuatorTest()
{
    m_dof <<   0., 0., 0., 0., 0., 0.,
                0., 0., 0., 0., 0., 0.;
}

double ActuatorTest::getInputPos(uint8_t index)
{
    return m_dof(POS, index);
}

void ActuatorTest::reset()
{

}

Eigen::Matrix<double, 2, 6>& ActuatorTest::sample()
{
    static uint16_t count = 0;

    if (count > 100 && count <= 200)
    {
        m_dof(VEL, 2) = 0.05;
    }
    else if (count > 200 && count <= 300)
    {
        m_dof(VEL, 2) = 0.;
    }
    else if (count > 300 && count <= 400)
    {
        m_dof(VEL, 2) = -0.05;
    }
    else
    {
        m_dof(VEL, 2) = 0;
    }

    count++;


    return m_dof;
}
