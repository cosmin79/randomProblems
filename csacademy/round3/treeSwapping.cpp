#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int NMAX = 100505;
// delta[node] = how many unmatched red and blue nodes in the subtree rooted at node
// since there can't both be positive (otherwise we would match them), we keep this
// as a difference (red -> +1, blue -> -1)
int N, delta[NMAX], par[NMAX];
char col[NMAX];
vector<int> G[NMAX];
bool redNode[NMAX], mark[NMAX];

long long cost[NMAX];

void read() {
    scanf("%d\n", &N);
    fgets(col + 1, NMAX, stdin);
    for (int i = 1; i <= N; i++) {
        redNode[i] = (col[i] == 'R');
    }

    int x, y;
    for (int i = 1; i < N; i++) {
        scanf("%d%d", &x, &y);
        G[x].push_back(y); G[y].push_back(x);
    }
}

inline int specAbs(int x) {
    return x < 0 ? -x : x;
}

void dfs(int node, bool expectedRed) {
    mark[node] = true;

    for (auto& x: G[node]) {
        if (!mark[x]) {
            par[x] = node;
            dfs(x, !expectedRed);
        }
    }

    // bring all the unmatch reds and blues to this subtree
    for (auto& x: G[node]) {
        if (par[x] == node) {
            cost[node] += cost[x] + specAbs(delta[x]);
            delta[node] += delta[x];
        }
    }

    // is the colour of the current node wrong?
    if (expectedRed != redNode[node]) {
        delta[node] += expectedRed ? -1 : 1;
    }
}

long long solve(bool redRoot) {
    memset(delta, 0, sizeof(delta));
    memset(cost, 0, sizeof(cost));
    memset(mark, false, sizeof(mark));

    dfs(1, redRoot);

    return delta[1] == 0 ? cost[1] : -1;
}

inline long long decide(long long sol1, long long sol2) {
    if (sol1 == -1) {
        return sol2;
    } else if (sol2 == -1) {
        return sol1;
    }

    return min(sol1, sol2);
}

int main() {
    //freopen("treeSwapping.in", "r", stdin);

    read();
    printf("%lld\n", decide(solve(false), solve(true)));
    return 0;
}