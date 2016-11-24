#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int NMAX = 1000505;
const int MOD = 1000000007;

int N, A[NMAX], noSecvs[NMAX], result[NMAX];

void read() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
}

void solve() {
    noSecvs[0] = noSecvs[1] = 1;
    for (int i = 2; i <= N; i++) {
        noSecvs[i] = (noSecvs[i - 1] * 2) % MOD;
    }

    long long curr, currSum;
    for (int i = 1; i <= N; i++) {
        curr = currSum = 0;
        for (int j = i; j >= 1; j--) {
            curr += result[j - 1];
            currSum += A[j];
            if (currSum >= MOD) {
                currSum -= MOD;
            }

            curr += ((1LL * currSum * (i - j + 1)) % MOD * noSecvs[j - 1]) % MOD;
        }

        result[i] = curr % MOD;
    }

    printf("%d\n", result[N]);
}

int main() {
    freopen("summingPieces.in", "r", stdin);

    read(); 
    solve();
    return 0;
}

