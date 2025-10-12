#include <bits/stdc++.h>
using namespace std;

struct Road {
    int from_num;
    int to_num;
    double distance;
};

int main() {
    int M;
    cin >> M;
    const int MAXM = 10;

    vector<Road> roads(M);
    for (int i = 0; i < M; ++i) {
        cin >> roads[i].from_num;
        cin >> roads[i].to_num;
        cin >> roads[i].distance;
    }

    double g[MAXM][MAXM];
    for (int i = 0; i < MAXM; ++i)
        for (int j = 0; j < MAXM; ++j)
            g[i][j] = -1.0;

    for (int i = 0; i < M; ++i) {
        int a = roads[i].from_num;
        int b = roads[i].to_num;
        double d = roads[i].distance;
        if (a >= 0 && a < MAXM && b >= 0 && b < MAXM) {
            g[a][b] = d;
            g[b][a] = d;
        }
    }

    vector<int> permutation;
    for (int i = 0; i < MAXM; ++i) {
    permutation.push_back(i);
	}
    
    double best_len = 1e300;
    vector<int> best_path;

    do {
        if (permutation[0] != 0) continue;

        bool ok = true;
        double sum = 0.0;

        for (int i = 0; i + 1 < MAXM; ++i) {
            int u = permutation[i];
            int v = permutation[i + 1];
            if (g[u][v] < 0) { ok = false; break; }
            sum += g[u][v];
        }

        if (!ok) continue;

        int last = permutation[MAXM - 1];
        if (g[last][0] < 0) continue;
        sum += g[last][0];

        if (sum < best_len) {
            best_len = sum;
            best_path = permutation;
            best_path.push_back(0);
        }

    } while (next_permutation(permutation.begin(), permutation.end()));

    if (best_len == 1e300) {
        cout << "NO SOLUTION\n";
    } else {
        cout << best_len << "\n";
        for (size_t i = 0; i < best_path.size(); ++i) {
            if (i) cout << ' ';
            cout << best_path[i];
        }
        cout << "\n";
    }

    return 0;
}
