#include "neutral.h"

Neutral::Neutral()
    : m_neutralPosition(0.0485)
{
    m_dof <<   0., 0., 0., 0., 0., 0.,
                0., 0., 0., 0., 0., 0.;
    m_heave = 0.003;
}

double Neutral::getInputPos(uint8_t index)
{
    return m_dof(POS, index);
}

void Neutral::reset()
{
    m_heave = 0.003;
}

Eigen::Matrix<double, 2, 6>& Neutral::sample()
{
    static double new_K = 0.01;
    static double prev_K = 1. - new_K;

    m_heave = new_K * m_neutralPosition + prev_K * m_heave;

    m_dof(POS, 2) = m_heave;

    return m_dof;
}
