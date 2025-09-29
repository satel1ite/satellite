#include <iostream>
#include <cmath>
#include <vector>

int main() {
	int max_length = 0;

	for (int i = 1; i < 101; i++) {
		std::vector<int> sp;
		int n = i;
		sp.push_back(n);

		while (n != 1) {
			if (n % 2 == 0)
				n = n / 2;
			else
				n = 3 * n + 1;
			sp.push_back(n);
		}

		if (sp.size() > max_length)
			max_length = sp.size();
	}
	std::cout << max_length << std::endl;
}