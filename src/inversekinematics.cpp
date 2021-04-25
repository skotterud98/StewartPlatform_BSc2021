#include "inversekinematics.h"

InverseKinematics::InverseKinematics() :
    // Base plate position vectors
    a1((Eigen::Vector3d() <<  -0.14228, -0.0475, 0.).finished()),
    a2((Eigen::Vector3d() << -0.11228, -0.09947, 0.).finished()),
    a3((Eigen::Vector3d() << -0.11228, -0.09947, 0.).finished()),
    a4((Eigen::Vector3d() << 0.14228, -0.0475, 0.).finished()),
    a5((Eigen::Vector3d() << 0.03, 0.14697, 0.).finished()),
    a6((Eigen::Vector3d() << -0.03, 0.14967, 0.).finished()),

    // Tool plate position vectors
    b1((Eigen::Vector3d() <<  -0.09761, 0.02172, 0.).finished()),
    b2((Eigen::Vector3d() << -0.030, -0.09539, 0.).finished()),
    b3((Eigen::Vector3d() << 0.030, -0.09539, 0.).finished()),
    b4((Eigen::Vector3d() << 0.09761, 0.02172, 0.).finished()),
    b5((Eigen::Vector3d() << 0.06761, 0.07368, 0.).finished()),
    b6((Eigen::Vector3d() << -0.06761, 0.07368, 0.).finished())
{

}
