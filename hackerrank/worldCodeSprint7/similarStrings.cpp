#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <unordered_map>
using namespace std;
// O(N ^ 2) sol

const int NMAX = 50505;
const int LGMAX = 17;
const int BASE = 51047;
const int LMAX = 10;
const int MOD = 1000000007;
const int UNDEF = BASE - 1;
int N, Q, ans[NMAX];
char A[NMAX];

struct query {
    int start, l;
};
query queries[NMAX];

int hash[LGMAX][NMAX], BB[NMAX], steps;
vector<int> fstAp[LGMAX][NMAX], lstAp[LGMAX][NMAX];

void read() {
    scanf("%d%d\n", &N, &Q);
    fgets(A + 1, NMAX, stdin);
    int x, y;
    for (int i = 1; i <= Q; i++) {
        scanf("%d%d", &x, &y);
        queries[i] = {x, y};
    }
}

void precompute() {
    BB[0] = 1;
    for (int i = 1; i < NMAX; i++) {
        BB[i] = (1LL * BB[i - 1] * BASE) % MOD;
    }

    while ((1 << steps) < N) {
        steps++;
    }
}

void cstrSuffixArray() {
    precompute();

    for (int i = step; i <= )

    // iter 0 
    for (int i = 1; i <= N; i++) {
        hash[0][i] = UNDEF;

    }
}

void solve() {
    cstrSuffixArray();
}

int main() {
    freopen("similarStrings.in", "r", stdin);
    read();
    solve();
    return 0;
}