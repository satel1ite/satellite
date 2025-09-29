#include <iostream>

int log2(long n) {
    if (n <= 0) return -1;

    int log = 0;
    while (n >>= 1) {
        log++;
    }
    return log;
}

int main() {
    long x;
    std::cin >> x;
    std::cout << log2(x) << std::endl;
}
