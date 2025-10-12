#include <iostream>
#include <bitset>
using namespace std;

int main() {
    int n;
    cin >> n;
    n &= 31;

    int gray = n ^ (n >> 1);

    int g = gray;
    int decode = g;
    while (g >>= 1) decode ^= g;

    cout << bitset<5>(n) << ' ' << bitset<5>(gray) << ' ' << bitset<5>(decode) << '\n';
    return 0;
}
