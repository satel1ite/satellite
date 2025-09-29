#include <iostream>
#include <cmath>
#include <vector>

int main() {
	int a, b;
	std::cin >> a >> b;

	int x = a;
	int y = b;

	while (y != 0) {
		int temp = y;
		y = x % y;
		x = temp;
	}
	std::cout << x << std::endl;
}