#include <iostream>
#include <cstdint>

int main() {
    long long N;
    std::cin >> N;         
    if (N < 0 || N > 50) {
        return 0;
    }

    if (N == 0) { std::cout << 0 << '\n'; return 0; }
    if (N == 1) { std::cout << 1 << '\n'; return 0; }

    unsigned long long prev = 0;
    unsigned long long cur = 1;
    for (long long i = 2; i <= N; ++i) {
        unsigned long long nxt = prev + cur;
        prev = cur;
        cur = nxt;
    }
    std::cout << cur << '\n';
    return 0;
}