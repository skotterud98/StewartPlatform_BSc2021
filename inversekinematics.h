#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#include <Eigen/Dense>
#include <vector>
#include <math.h>

#define PI 3.14159265358979323846

class InverseKinematics
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    InverseKinematics();

    void calc_legs(Eigen::Matrix<double, 2, 6>& Input);
private:
    enum pos_vel { POS = 0, VEL = 1 };
    const Eigen::Vector3d a1, a2, a3, a4, a5, a6;
    const Eigen::Vector3d b1, b2, b3, b4, b5, b6;

    const double z_min;
    const double l_min;

    double d1, d2, d3, d4, d5, d6;
};

#endif // INVERSEKINEMATICS_H
