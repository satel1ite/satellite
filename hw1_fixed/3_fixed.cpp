#include <iostream>
#include <cmath>


int main() {
	double a, b, c;
	double d;
	const double cEps = 1e-9;
	std::cin >> a >> b >> c;

	d = std::pow(b, 2) - 4 * a * c;
	double x1, x2;
	if (d < -cEps) {
		std::cout << "there are no solution in real numbers" << std::endl;
	}	
	else if (std::abs(d) <= cEps) {
		x1 = -b / (2 * a);
		std::cout << x1 << std::endl;
	}

	else {
		x1 = (-b + std::sqrt(d)) / (2 * a);
		x2 = (-b - std::sqrt(d)) / (2 * a);
		std::cout << x1 << " " << x2 << std::endl;
	}


}