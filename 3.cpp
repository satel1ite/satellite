#include <iostream>
#include <cmath>
#include <clocale>

int main() {
	std::setlocale(LC_ALL, "");
	double a, b, c;
	double d;
	std::cin >> a >> b >> c;
	d = std::pow(b, 2) - 4 * a * c;
	double x1, x2;
	if (d < 0) {
		std::cout << "нет корней в вещественных числах" << std::endl;
	}

	if (d == 0) {
		x1 = -b / (2 * a);
		std::cout << x1 << std::endl;
	}

	if (d > 0) {
		x1 = (-b + std::sqrt(d)) / (2 * a);
		x2 = (-b - std::sqrt(d)) / (2 * a);
		std::cout << x1 << " " << x2 << std::endl;
	}


}