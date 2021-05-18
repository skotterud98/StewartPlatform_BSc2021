#include "rampneutral.h"

RampNeutral::RampNeutral()
    : m_neutralPosition(0.0485)
{
    m_dof <<   0., 0., 0., 0., 0., 0.,
                0., 0., 0., 0., 0., 0.;
    m_heave = 0.003;
}

double RampNeutral::getInputPos(uint8_t index)
{
    return m_dof(POS, index);
}

void RampNeutral::reset()
{
    m_heave = 0.003;
}

Eigen::Matrix<double, 2, 6>& RampNeutral::sample()
{
    static double new_K = 0.007;
    static double prev_K = 1. - new_K;

    m_heave = new_K * m_neutralPosition + prev_K * m_heave;

    m_dof(POS, HEAVE) = m_heave;

    return m_dof;
}
