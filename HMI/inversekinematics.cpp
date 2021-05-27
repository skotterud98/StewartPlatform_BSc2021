#include "inversekinematics.h"

InverseKinematics::InverseKinematics() :
    // Base plate position vectors (x, y, z)
    a1((Eigen::Vector3d() <<  -0.1422792, -0.0475039, 0.).finished()),
    a2((Eigen::Vector3d() << -0.1122792, -0.0994655, 0.).finished()),
    a3((Eigen::Vector3d() << 0.1122792, -0.0994655, 0.).finished()),
    a4((Eigen::Vector3d() << 0.1422792, -0.0475039, 0.).finished()),
    a5((Eigen::Vector3d() << 0.03, 0.1469694, 0.).finished()),
    a6((Eigen::Vector3d() << -0.03, 0.1469694, 0.).finished()),

    // Tool plate position vectors (x, y, z)
    b1((Eigen::Vector3d() <<  -0.0975471, 0.0218188, 0.).finished()),
    b2((Eigen::Vector3d() << -0.0298778, -0.0953878, 0.).finished()),
    b3((Eigen::Vector3d() << 0.0298778, -0.0953878, 0.).finished()),
    b4((Eigen::Vector3d() << 0.0975471, 0.0218188, 0.).finished()),
    b5((Eigen::Vector3d() << 0.0676694, 0.0735689, 0.).finished()),
    b6((Eigen::Vector3d() << -0.0676694, 0.0735689, 0.).finished()),

    // Minimum heave (z) possible
    z_min(0.16107),

    // Minimum leg length (stroke = 0)
    l_min(0.181)
{
    // Empty body
}

void InverseKinematics::calc_legs(Eigen::Matrix<double, 2, 6>& _input)
{
    static Eigen::Vector3d p;
    static double phi_sin, phi_cos, theta_sin, theta_cos, psi_sin, psi_cos;
    static Eigen::Matrix3d R_x, R_y, R_z, R;
    static Eigen::Matrix<double, 6, 1> twist;

    // Twist vector
    twist << _input(VEL, 0), _input(VEL, 1), _input(VEL, 2), _input(VEL, 3), _input(VEL, 4), _input(VEL, 5);

    // Position vector (x, y, z)
    p <<    _input(POS, 0),                     // Surge
            _input(POS, 1),                     // Sway
            this->z_min + _input(POS, 2);       // Heave

    // Sin and cos values
    phi_sin = sin(_input(POS, 3));              // Roll
    phi_cos = cos(_input(POS, 3));

    theta_sin = sin(_input(POS, 4));            // Pitch
    theta_cos = cos(_input(POS, 4));

    psi_sin = sin(_input(POS, 5));              // Yaw
    psi_cos = cos(_input(POS, 5));


    // Rotation matrices for each axis of rotation
    R_x <<  1., 0., 0.,
            0., phi_cos, -phi_sin,
            0., phi_sin, phi_cos;

    R_y <<  theta_cos, 0., theta_sin,
            0., 1., 0.,
            -theta_sin, 0., theta_cos;

    R_z <<  psi_cos, -psi_sin, 0.,
            psi_sin, psi_cos, 0.,
            0., 0., 1.;

    // Total rotation matrix
    R = R_z * R_y * R_x;

    // Leg vectors
    static Eigen::Vector3d s1, s2, s3, s4, s5, s6;

    s1 = p + (R * this->b1) - this->a1;
    s2 = p + (R * this->b2) - this->a2;
    s3 = p + (R * this->b3) - this->a3;
    s4 = p + (R * this->b4) - this->a4;
    s5 = p + (R * this->b5) - this->a5;
    s6 = p + (R * this->b6) - this->a6;

    // Leg lengths (leg vector magnitude)
    static double l1, l2, l3, l4, l5, l6;
    l1 = s1.norm();
    l2 = s2.norm();
    l3 = s3.norm();
    l4 = s4.norm();
    l5 = s5.norm();
    l6 = s6.norm();


    // Actuator stroke
    d1 = l1 - this->l_min;
    d2 = l2 - this->l_min;
    d3 = l3 - this->l_min;
    d4 = l4 - this->l_min;
    d5 = l5 - this->l_min;
    d6 = l6 - this->l_min;

    // Leg unit vector
    static Eigen::Vector3d e1, e2, e3, e4, e5, e6;
    e1 = s1 / l1;
    e2 = s2 / l2;
    e3 = s3 / l3;
    e4 = s4 / l4;
    e5 = s5 / l5;
    e6 = s6 / l6;

    // Jacobian
    static Eigen::Matrix<double, 6, 6> J;
    J <<    e1.transpose(), ((R * this->b1).cross(e1)).transpose(),
            e2.transpose(), ((R * this->b2).cross(e2)).transpose(),
            e3.transpose(), ((R * this->b3).cross(e3)).transpose(),
            e4.transpose(), ((R * this->b4).cross(e4)).transpose(),
            e5.transpose(), ((R * this->b5).cross(e5)).transpose(),
            e6.transpose(), ((R * this->b6).cross(e6)).transpose();

    // Stroke velocity
    static Eigen::Matrix<double, 6, 1> d_dot;
    d_dot = J * twist;

    // Store leg stroke position (d) and leg stroke velocity (d_dot) in the referenced input-variable
    _input <<   d1,         d2,         d3,         d4,         d5,         d6,
                d_dot[0],   d_dot[1],   d_dot[2],   d_dot[3],   d_dot[4],   d_dot[5];
}





























