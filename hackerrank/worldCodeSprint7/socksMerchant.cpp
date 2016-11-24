#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const int NMAX = 105;
int N, cnt[NMAX];

int main() {
    freopen("socksMerchant.in", "r", stdin);

    scanf("%d", &N);
    int x;
    for (int i = 0; i < N; i++) {
        scanf("%d", &x);
        cnt[x]++;
    }

    int result = 0;
    for (int i = 0; i < NMAX; i++) {
        result += cnt[i] / 2;
    }

    printf("%d\n", result);
    return 0;
}

