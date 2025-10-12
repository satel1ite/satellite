#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

struct Rectangle {
    int lx, ly, rx, ry;
};

int main() {
    long long N;
    cin >> N;
    if (N <= 0) {
        cout << "0 0 0 0\n";
        return 0;
    }

    Rectangle r;
    cin >> r.lx >> r.ly >> r.rx >> r.ry;

    int lx_min = r.lx;
    int ly_max = r.ly;
    int rx_max = r.rx;
    int ry_min = r.ry;

    for (int i = 1; i < N; i++) {
        cin >> r.lx >> r.ly >> r.rx >> r.ry;
        lx_min = min(lx_min, r.lx);
        ly_max = max(ly_max, r.ly);
        rx_max = max(rx_max, r.rx);
        ry_min = min(ry_min, r.ry);  
    }

    if (lx_min == rx_max || ly_max == ry_min) {
        cout << lx_min << " " << ly_max << " 0 0\n";
    } else {
        cout << lx_min << " " << ly_max << " " << rx_max << " " << ry_min << "\n";
    }

    return 0;
}
