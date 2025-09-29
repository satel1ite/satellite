#include <iostream>

int log2_double(double x) {
    if (x <= 0) return -999999;

    int log = 0;

    while (x >= 2.0) {
        x /= 2.0;
        log++;
    }

    while (x < 1.0) {
        x *= 2.0;
        log--;
    }

    return log;
}

int main() {
    double y;
    std::cin >> y;
    std::cout << "floor(log2(" << y << ")) = " << log2_double(y) << std::endl;
}
