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

    int lx1 = r.lx;
    int ly1 = r.ly;
    int rx1 = r.rx;
    int ry1 = r.ry;

    for (int i = 1; i < N; i++) {
        cin >> r.lx >> r.ly >> r.rx >> r.ry;
        lx1 = max(lx1, r.lx);
        ly1 = min(ly1, r.ly);
        rx1 = min(rx1, r.rx);
        ry1 = max(ry1, r.ry);
    }

    if (lx1 <= rx1 && ly1 >= ry1) {
        if (lx1 == rx1 || ly1 == ry1) {
            cout << lx1 << " " << ly1 << " 0 0\n";
        } else {
            cout << lx1 << " " << ly1 << " " << rx1 << " " << ry1 << "\n";
        }
    } else {
        cout << "0 0 0 0\n";
    }

    return 0;
}
