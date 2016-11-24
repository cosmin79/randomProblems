#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int N;
vector<vector<int>> G, GT;
vector<bool> mark, sol, validNode;

void addEdge(int x, int y) {
    G[x].push_back(y);
    GT[y].push_back(x);
}

inline int negatevar(int x) {
    return x > N ? x - N : x + N;
}

void addOrEdge(int x, int y) {
    addEdge(negatevar(x), y);
    addEdge(negatevar(y), x);
}

void dfs1(int node, vector<int>& topoSort) {
    mark[node] = true;
    for (auto& x: G[node]) {
        if (validNode[x] && !mark[x]) {
            dfs1(x, topoSort);
        }
    }

    topoSort.push_back(node);
}

bool dfs2(int node) {
    if (sol[node]) {
        return false;
    }
    sol[negatevar(node)] = true;
    mark[node] = true;

    bool sol = true;
    for (auto& x: GT[node]) {
        if (validNode[x] && !mark[x]) {
            sol &= dfs2(x);
        }
    }

    return sol;
}

void init(int _N) {
    N = _N;
    G.assign(2 * N + 1, vector<int>());
    GT.assign(2 * N + 1, vector<int>());
    mark.assign(2 * N + 1, false);
    sol.assign(2 * N + 1, false);
}

bool solveTwoSat(int from, int to) {
    validNode.assign(2 * N + 1, false);
    for (int i = from; i <= to; i++) {
        validNode[i] = true;
        validNode[negatevar(i)] = true;
    }
    mark.assign(2 * N + 1, false);
    sol.assign(2 * N + 1, false);

    vector<int> topoSort;
    topoSort.reserve(2 * N);
    for (int i = from; i <= to; i++) {
        if (!mark[i]) {
            dfs1(i, topoSort);
        }
    }

    reverse(topoSort.begin(), topoSort.end());
    mark.assign(2 * N + 1, false);

    bool solExists = true;
    for (auto& node: topoSort) {
        if (!mark[node] && !mark[negatevar(node)]) {
            solExists &= dfs2(node);
        }
    }

    return solExists;
}

const int NMAX = 105;
int Q, NN;

struct segment {
    int x, y;

    inline bool nonIntersect(segment& other) {
        return y < other.x || other.y < x;
    }

    inline bool intersect(segment& other) {
        return !nonIntersect(other);
    }
};
segment live[NMAX], repeat[NMAX];

void read() {
    scanf("%d", &NN);
    for (int i = 1; i <= NN; i++) {
        scanf("%d%d%d%d", &live[i].x, &live[i].y, &repeat[i].x, &repeat[i].y);
    }
}

void prepare() {
    vector<segment> shows;
    for (int i = 1; i <= NN; i++) {
        shows.push_back(live[i]);
        shows.push_back(repeat[i]);
    }
    init(shows.size());

    for (size_t i = 0; i < shows.size(); i += 2) {
        // live[i] <-> ~repeat[i]
        addOrEdge(negatevar(i + 1), negatevar(i + 2));
        addOrEdge(i + 1, i + 2);
    }

    for (size_t i = 0; i < shows.size(); i++) {
        for (size_t j = i + 1; j < shows.size(); j++) {
            if (shows[i].intersect(shows[j])) {
                // ~x_i | ~x_j
                addOrEdge(negatevar(i + 1), negatevar(j + 1));
            }
        }
    }
}

bool ok(int from, int to) {
    return solveTwoSat(2 * from - 1, 2 * to);
}

int bsearch(int startIdx) {
    int i, step;
    for (step = 1; step <= NN - startIdx + 1; step <<= 1);

    for (i = startIdx; step; step >>= 1) {
        if (i + step <= NN && ok(startIdx, i + step)) {
            i += step;
        }
    }

    return i;
}

void solve() {
    int bestInterv = 0, bestL;
    for (int startIdx = 1; startIdx <= NN; startIdx++) {
        int latestIdx = bsearch(startIdx);

        if (latestIdx - startIdx + 1 > bestInterv) {
            bestInterv = latestIdx - startIdx + 1;
            bestL = startIdx;
        }
    }

    printf("%d %d\n", bestL, bestL + bestInterv - 1);
}

void clear() {
    G.clear();
    GT.clear();
    mark.clear();
    sol.clear();
    validNode.clear();
}

int main() {
    //freopen("recordEpisodes.in", "r", stdin);

    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        read();
        prepare();
        solve();
        clear();
    }
    return 0;
}

