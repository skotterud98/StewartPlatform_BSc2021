#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#include <Eigen/Dense>
#include <vector>

#define PI 3.14159265358979323846

class InverseKinematics
{
public:
    InverseKinematics();

    Eigen::Matrix<float, 6, 6> calc_output(float pose[], float twist[]);

private:
    Eigen::Matrix<float, 6, 6> jacobian();

    const Eigen::Vector3d a1, a2, a3, a4, a5, a6;
    const Eigen::Vector3d b1, b2, b3, b4, b5, b6;
};

#endif // INVERSEKINEMATICS_H
