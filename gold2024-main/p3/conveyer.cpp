#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000;
int N, Q;
vector<int> parent, size, hasCycle, touchesBoundary;

int dr[] = {0, 0, -1, 1};
int dc[] = {-1, 1, 0, 0};
char directions[] = {'L', 'R', 'U', 'D'};

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unionSets(int u, int v, int &totalUnusable) {
    u = find(u);
    v = find(v);

    if (u == v) {
        if (!hasCycle[u]) {
            hasCycle[u] = 1;
            totalUnusable += size[u];
        }
    } else {
        if (size[u] < size[v]) swap(u, v);
        parent[v] = u;

        if (hasCycle[u] || hasCycle[v]) {
            if (!hasCycle[u]) totalUnusable += size[u];
            if (!hasCycle[v]) totalUnusable += size[v];
            hasCycle[u] = 1;
        }

        if (touchesBoundary[u] || touchesBoundary[v]) {
            touchesBoundary[u] = 1;
            hasCycle[u] = 0;
            totalUnusable -= size[u];
        }

        size[u] += size[v];
    }
}

int cellId(int r, int c) {
    return r * N + c;
}

bool inGrid(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < N;
}

pair<int, int> move(int r, int c, char dir) {
    if (dir == 'L') return {r, c - 1};
    if (dir == 'R') return {r, c + 1};
    if (dir == 'U') return {r - 1, c};
    if (dir == 'D') return {r + 1, c};
    return {-1, -1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> Q;

    parent.resize(N * N);
    size.resize(N * N, 1);
    hasCycle.resize(N * N, 0);
    touchesBoundary.resize(N * N, 0);

    for (int i = 0; i < N * N; i++) {
        parent[i] = i;

        int r = i / N, c = i % N;
        if (r == 0 || r == N - 1 || c == 0 || c == N - 1) {
            touchesBoundary[i] = 1;
        }
    }

    vector<vector<char>> grid(N, vector<char>(N, '?'));
    int totalUnusable = 0;

    for (int i = 0; i < Q; i++) {
        int r, c;
        char dir;
        cin >> r >> c >> dir;
        r--, c--;

        grid[r][c] = dir;
        int u = cellId(r, c);

        auto [nr, nc] = move(r, c, dir);
        if (inGrid(nr, nc)) {
            int v = cellId(nr, nc);
            unionSets(u, v, totalUnusable);
        }

        cout << totalUnusable << "\n";
    }

    return 0;
}
