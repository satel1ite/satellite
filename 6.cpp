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
	char s1[101], s2[101];
	std::cin.getline(s1, 101);
	std::cin.getline(s2, 101);

	int max_len = 0;
	int st_ind = 0;

	int len1 = strlen(s1);
	int len2 = strlen(s2);

	for (int i = 0; i < len1; i++) {
		for (int j = i; j < len1; j++) {
			int sub_len = j - i + 1;

			for (int k = 0; k <= len2 - sub_len; k++) {
				if (strncmp(s1 + i, s2 + k, sub_len) == 0) {
					if (sub_len > max_len) {
						max_len = sub_len;
						st_ind = i;
					}
				}
			}
		}
	}
	for (int i = 0; i < max_len; i++)
		std::cout << s1[st_ind + i];
	return 0;
}