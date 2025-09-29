#include <iostream>
#include <cmath>

int main() {
    int N;
    std::cin >> N;
    if (N < 0 || N > 50) return 0;

    double sqrt5 = std::sqrt(5.0);
    double phi = (1.0 + sqrt5) / 2.0;
    double psi = (1.0 - sqrt5) / 2.0;

    double value = (std::pow(phi, N) - std::pow(psi, N)) / sqrt5;


    unsigned long long result = value + 0.5;


    std::cout << result << std::endl;
    return 0;
}
