#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int NMAX = 1000505;
const int MOD = 1000000007;

int N, A[NMAX], noSecvs[NMAX], result[NMAX];
int S[NMAX], X[NMAX], Y[NMAX], sumNoSecvs[NMAX];

void read() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
        S[i] = S[i - 1] + A[i];
        if (S[i] >= MOD) {
            S[i] -= MOD;
        }
    }
}

inline int getSum(int x, int y) {
    int result = S[y] - S[x - 1];
    return result < 0 ? result + MOD : result;
}

inline void mod(int& x) {
    if (x < 0) {
        x += MOD;
    } else if (x >= MOD) {
        x -= MOD;
    }
}

void solve() {
    noSecvs[0] = noSecvs[1] = 1;
    sumNoSecvs[0] = 1; sumNoSecvs[1] = 2;
    for (int i = 2; i <= N; i++) {
        noSecvs[i] = (noSecvs[i - 1] * 2) % MOD;
        sumNoSecvs[i] = (sumNoSecvs[i - 1] + noSecvs[i]) % MOD;
    }

    int curr;
    for (int i = 1; i <= N; i++) {
        // j = N
        curr = result[i - 1] + (1LL * A[i] * noSecvs[i - 1]) % MOD;
        mod(curr);

        /*for (int j = 1; j < i; j++) {
            curr += (1LL * noSecvs[j - 1] * (1LL * A[i] * (i - j + 1) + getSum(j, i - 1)) % MOD) % MOD;
            mod(curr);
        }*/

        if (i > 1) {
            X[i] = (X[i - 1] + sumNoSecvs[i - 2]) % MOD + noSecvs[i - 2];
        }
        mod(X[i]);

        curr += (1LL * A[i] * X[i]) % MOD;
        mod(curr);

        if (i > 1) {
            Y[i] = Y[i - 1] + (1LL * sumNoSecvs[i - 2] * A[i - 1]) % MOD;
            mod(Y[i]);
        }

        curr += Y[i];
        mod(curr);
        
        /*for (int j = 1; j < i; j++) {
            curr += (1LL * noSecvs[j - 1] * getSum(j, i - 1)) % MOD;
            mod(curr);
        }*/

        result[i] = result[i - 1] + curr;
        mod(result[i]);
    }

    printf("%d\n", result[N]);
}

int main() {
    freopen("summingPieces.in", "r", stdin);

    read(); 
    solve();
    return 0;
}

