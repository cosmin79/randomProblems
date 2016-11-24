#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
const int NMAX = 55;
const int LMAX = 1055;
const int MOD = 1000000007;

int Q, N, pos[LMAX], r;
char A[LMAX];
string S;

int cnt[LMAX][LMAX];
void read() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> S;
        
        for (auto& ch: S) {
            A[++r] = ch;
            pos[r] = i;
        }
    }
}

inline void mod(int &x) {
    if (x >= MOD) {
        x -= MOD;
    }
    if (x < 0) {
        x += MOD;
    }
}

void solve() {
    for (int i = 1; i <= r; i++) {
        cnt[i][i] = 1;
    }

    for (int l = 2; l <= r; l++) {
        for (int i = 1; i <= r - l + 1; i++) {
            int lft = i, rght = i + l - 1;

            if (A[lft] == A[rght]) {
                // take l, r
                cnt[lft][rght] += 1 + cnt[lft + 1][rght - 1];
            }
            mod(cnt[lft][rght]);

            // don't take it
            cnt[lft][rght] += cnt[lft + 1][rght];
            mod(cnt[lft][rght]);
            cnt[lft][rght] += cnt[lft][rght - 1];
            mod(cnt[lft][rght]);

            cnt[lft][rght] -= cnt[lft + 1][rght - 1];
            mod(cnt[lft][rght]);
        }
    }

    printf("%d\n", cnt[1][r]);
}

void clear() {
    r = 0;
    memset(cnt, 0, sizeof(cnt));
}

int main() {
    freopen("palindromicString.in", "r", stdin);

    cin >> Q;
    while (Q--) {
        read();
        solve();

        clear();
    }
    return 0;
}