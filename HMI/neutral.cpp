#include "neutral.h"

Neutral::Neutral()
    : m_neutralPosition(0.0485)
{
    m_dof <<   0., 0., 0., 0., 0., 0.,
                0., 0., 0., 0., 0., 0.;
}

double Neutral::getInputPos(uint8_t index)
{
    return m_dof(POS, index);
}

void Neutral::reset()
{
    // Empty body
}

Eigen::Matrix<double, 2, 6>& Neutral::sample()
{
    m_dof(POS, HEAVE) = m_neutralPosition;

    return m_dof;
}

