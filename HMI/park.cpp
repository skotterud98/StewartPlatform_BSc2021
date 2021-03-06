#include "park.h"

Park::Park()
    : m_parkPosition(0.005)
{
    m_dof <<   0., 0., 0., 0., 0., 0.,
                0., 0., 0., 0., 0., 0.;
    m_heave = m_parkPosition;
}

double Park::getInputPos(uint8_t index)
{
    return m_dof(POS, index);
}

void Park::reset()
{
    m_heave = 0.0485;
}

Eigen::Matrix<double, 2, 6>& Park::sample()
{
    static double new_K = 0.007;
    static double prev_K = 1. - new_K;

    m_heave = new_K * m_parkPosition + prev_K * m_heave;

    m_dof(POS, HEAVE) = m_heave;

    return m_dof;
}
