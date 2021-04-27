#include "inversekinematics.h"
#include <iostream>
#include <vector>
#include "Eigen/Dense"

int main()
{
	
	InverseKinematics* ik = new InverseKinematics();
	
	std::vector<std::vector<double>> output(2, std::vector<double>(6));
	
	double pose[6] = {0., 0., 0.048, 0., 0.05, 0.05 };
	Eigen::Matrix<double, 6, 1> twist;
	
	twist << 0.02, 0.02, 0.02, 0.02, 0.03, 0.02;
	
	ik->calc_output(output, pose, twist);
	
	for (int i = 0; i < 6; i++)
	{
		std::cout << output[0][i] << "\t";
	}
	
	std::cout << "\n";
	
	for (int i = 0; i < 6; i++)
	{
		std::cout << output[1][i] << "\t";
	}
	std::cout << "\n";
	
	delete ik;
}
