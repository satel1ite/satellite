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

    int lx1 = r.lx;
    int ly1 = r.ly;
    int rx1 = r.rx;
    int ry1 = r.ry;

    for (int i = 1; i < N; i++) {
        std::cin >> r.lx >> r.ly >> r.rx >> r.ry;
        lx1 = std::max(lx1, r.lx);
        ly1 = std::min(ly1, r.ly);
        rx1 = std::min(rx1, r.rx);
        ry1 = std::max(ry1, r.ry);
    }

    if (lx1 <= rx1 && ly1 >= ry1) {
        if (lx1 == rx1 || ly1 == ry1) {
            std::cout << lx1 << " " << ly1 << " 0 0\n";
        } else {
            std::cout << lx1 << " " << ly1 << " " << rx1 << " " << ry1 << "\n";
        }
    } else {
        std::cout << "0 0 0 0\n";
    }

    return 0;
}
