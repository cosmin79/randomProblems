#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class twoSat {

private:
    int N;
    vector<vector<int>> G, GT;
    vector<bool> mark, sol;

    void addEdge(int x, int y) {
        G[x].push_back(y);
        GT[y].push_back(x);
    }

    void dfs1(int node, vector<int>& topoSort) {
        mark[node] = true;
        for (auto& x: G[node]) {
            if (!mark[x]) {
                dfs1(x, topoSort);
            }
        }

        topoSort.push_back(node);
    }

    bool dfs2(int node) {
        if (sol[node]) {
            return false;
        }
        sol[negate(node)] = true;
        mark[node] = true;

        bool sol = true;
        for (auto& x: GT[node]) {
            if (!mark[x]) {
                sol &= dfs2(x);
            }
        }

        return sol;
    }

public:
    twoSat(int _N) : N(_N) {
        G.assign(2 * N + 1, vector<int>());
        GT.assign(2 * N + 1, vector<int>());
        mark.assign(2 * N + 1, false);
        sol.assign(2 * N + 1, false);
    }

    int negate(int x) {
        return x > N ? x - N : x + N;
    }

    void addOrEdge(int x, int y) {
        addEdge(negate(x), y);
        addEdge(negate(y), x);
    }

    bool solve();

    vector<bool> getSol() {
        return vector<bool>(sol.begin() + 1, sol.begin() + N + 1);
    }
};

bool twoSat::solve() {
    vector<int> topoSort;
    topoSort.reserve(2 * N);
    for (int i = 1; i <= 2 * N; i++) {
        if (!mark[i]) {
            dfs1(i, topoSort);
        }
    }

    reverse(topoSort.begin(), topoSort.end());
    mark.assign(2 * N + 1, false);

    bool solExists = true;
    for (auto& node: topoSort) {
        if (!mark[node] && !mark[negate(node)]) {
            solExists &= dfs2(node);
        }
    }

    return solExists;
}

inline int encodeNode(int x, twoSat* &solver) {
    return x > 0 ? x : solver -> negate(-x);
}

int N, M;

int main() {
    freopen("2sat.in", "r", stdin);
    freopen("2sat.out", "w", stdout);

    scanf("%d%d", &N, &M);
    twoSat* solver = new twoSat(N);
    int x, y;
    for (int i = 1; i <= M; i++) {
        scanf("%d%d", &x, &y);
        solver -> addOrEdge(encodeNode(x, solver), encodeNode(y, solver));
    }

    bool result = solver -> solve();
    if (result) {
        vector<bool> sol = solver -> getSol();
        for (auto x: sol) {
            printf("%d ", (int)x);
        }
        printf("\n");
    } else {
        printf("-1\n");
    }
    return 0;
}

