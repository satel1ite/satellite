#include <iostream>
#include <cmath>
#include <clocale>
#include <vector>

int gcd(int a, int b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

int main() {
	std::setlocale(LC_ALL, "");
	int a, b;
	std::cin >> a >> b;
	std::cout << gcd(a, b) << std::endl;
}