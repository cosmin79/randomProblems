#include <cstdio>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
// O(N ^ 2) sol

const int NMAX = 50505;
const int BASE = 51047;
const int LMAX = 26;
const int MOD = 1000000007;
int N, Q, ans[NMAX];
char A[NMAX];

struct query {
    int start, queryIdx;
};
vector<query> queries[NMAX];

void read() {
    scanf("%d%d\n", &N, &Q);
    fgets(A + 1, NMAX, stdin);
    int x, y;
    for (int i = 1; i <= Q; i++) {
        scanf("%d%d", &x, &y);
        queries[y - x + 1].push_back({x, i});
    }
}

int hashSeq[NMAX];
int last[NMAX][LMAX];

inline int getLast(int idx, int pos) {
    int lastPos = last[idx][A[pos] - 'a'];
    return lastPos ? pos - lastPos : BASE - 1;
}

void update(int l) {
    if (queries[l].empty()) {
        return ;
    }
    unordered_map<int, int> cntHash;
    for (int i = 1; i <= N - l + 1; i++) {
        cntHash[hashSeq[i]]++;
    }

    for (auto& query: queries[l]) {
        ans[query.queryIdx] = cntHash[hashSeq[query.start]];
    }
}

void solve() {
    // init
    for (int i = 1; i <= N; i++) {
        hashSeq[i] = (1LL * hashSeq[i] * BASE + getLast(i, i)) % MOD;
        last[i][A[i] - 'a'] = i;
    }
    update(1);

    for (int l = 2; l <= N; l++) {
        for (int i = 1; i <= N - l + 1; i++) {
            hashSeq[i] = (1LL * hashSeq[i] * BASE + getLast(i, i + l - 1)) % MOD;
            last[i][A[i + l - 1] - 'a'] = i + l - 1;
        }
        update(l);
    }

    for (int i = 1; i <= Q; i++) {
        printf("%d\n", ans[i]);
    }
}

int main() {
    freopen("similarStrings.in", "r", stdin);
    read();
    solve();
    return 0;
}