#include <iostream>
#include <string>


int main() {

    int vals[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    std::string syms[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    for (int n = 1; n <= 1000; ++n) {
        int x = n;
        std::string roman;
        for (int i = 0; i < 13; ++i) {
            while (x >= vals[i]) {
                roman += syms[i];
                x -= vals[i];
            }
        }
        std::cout << roman << '\n';
    }

    return 0;
}
