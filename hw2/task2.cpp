#include <iostream>
#include <algorithm>
#include <climits>


struct Rectangle {
    int lx, ly, rx, ry;
};

int main() {
    long long N;
    std::cin >> N;
    if (N <= 0) {
        std::cout << "0 0 0 0\n";
        return 0;
    }

    Rectangle r;
    std::cin >> r.lx >> r.ly >> r.rx >> r.ry;

    int lx_min = r.lx;
    int ly_max = r.ly;
    int rx_max = r.rx;
    int ry_min = r.ry;

    for (int i = 1; i < N; i++) {
        std::cin >> r.lx >> r.ly >> r.rx >> r.ry;
        lx_min = std::min(lx_min, r.lx);
        ly_max = std::max(ly_max, r.ly);
        rx_max = std::max(rx_max, r.rx);
        ry_min = std::min(ry_min, r.ry);  
    }

    if (lx_min == rx_max || ly_max == ry_min) {
        std::cout << lx_min << " " << ly_max << " 0 0\n";
    } else {
        std::cout << lx_min << " " << ly_max << " " << rx_max << " " << ry_min << "\n";
    }

    return 0;
}
