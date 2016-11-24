#include <cstdio>
#include <algorithm>
using namespace std;
const int NMAX = 100505;

int N, A[NMAX], P[NMAX];
int par[NMAX], deg[NMAX];
long long valTree[NMAX];

bool valid[NMAX];

long long res[NMAX];

void read() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &P[i]);
    }
}

void initDSU() {
    for (int i = 1; i <= N; i++) {
        par[i] = i;
        valTree[i] = A[i];
    }
}

int findRoot(int node) {
    int y = node, aux;
    while (par[y] != y) {
        y = par[y];
    }
    while (par[node] != node) {
        aux = par[node];
        par[node] = y;
        node = aux;
    }
   
    return y;
}

void merge(int root1, int root2) {
    if (root1 == root2) {
        return ;
    }

    if (deg[root1] < deg[root2]) {
        par[root1] = root2;
        valTree[root2] += valTree[root1];
    } else {
        par[root2] = root1;
        valTree[root1] += valTree[root2];
        if (deg[root1] == deg[root2]) {
            deg[root1]++;
        }
    }
}

void solve() {
    initDSU();
    long long curr = 0;
    for (int i = N; i >= 1; i--) {
        int currIdx = P[i];
        valid[currIdx] = true;

        // update neighbours
        if (valid[currIdx - 1]) {
            merge(findRoot(currIdx - 1), findRoot(currIdx));
        }
        if (valid[currIdx + 1]) {
            merge(findRoot(currIdx + 1), findRoot(currIdx));
        }

        curr = max(curr, valTree[findRoot(currIdx)]);
        res[i] = curr;
    }

    for (int i = 2; i <= N; i++) {
        printf("%lld\n", res[i]);
    }
    printf("0\n");
}

int main() {
    freopen("C.in", "r", stdin);

    read();
    solve();
    return 0;
}