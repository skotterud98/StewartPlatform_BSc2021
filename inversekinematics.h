#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#include <Eigen/Dense>
#include <vector>
#include <math.h>

#define PI 3.14159265358979323846

enum pos_vel
{
    POS = 0,
    VEL = 1
};


class InverseKinematics
{
public:
    InverseKinematics();

    void calc_output(std::vector<std::vector<double>>& output, const double pose[], const double twist[]);
private:
    const Eigen::Vector3d a1, a2, a3, a4, a5, a6;
    const Eigen::Vector3d b1, b2, b3, b4, b5, b6;

    const double z_min;
    const double l_min;
};

#endif // INVERSEKINEMATICS_H
