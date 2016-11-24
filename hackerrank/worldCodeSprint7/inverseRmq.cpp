#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <unordered_map>
using namespace std;

const int NMAX = 1 << 19;
const int LMAX = 20;

int N, A[NMAX], sol[NMAX];
unordered_map<int, int> H;
vector<int> cnt[LMAX];

void read() {
    scanf("%d", &N);
    for (int i = 1; i <= 2 * N - 1; i++) {
        scanf("%d", &A[i]);
        H[A[i]]++;
    }
}

void solve() {
    int totalDepth = 1;
    while ((1 << totalDepth) <= N) {
        totalDepth++;
    }

    for (auto it = H.begin(); it != H.end(); it++) {
        if ((it -> second) > totalDepth) {
            printf("NO\n");
            return ;
        }
        cnt[it -> second].push_back(it -> first);
    }

    set<int> Q;
    if (cnt[totalDepth].size() != 1) {
        printf("NO\n");
        return ;
    }
    sol[1] = cnt[totalDepth][0];

    int currLvl = 2, last = 1;
    for (int lvl = 2; lvl <= totalDepth; lvl++) {
        if (cnt[totalDepth - lvl + 1].size() != currLvl / 2) {
            printf("NO\n");
            return ;
        }
        for (auto& val: cnt[totalDepth - lvl + 1]) {
            Q.insert(val);
        }

        int l = last - (currLvl >> 1) + 1;
        for (int i = l; i <= last; i++) {
            auto it = Q.lower_bound(sol[i]);
            if (it == Q.end()) {
                printf("NO\n");
                return ;
            }
            sol[2 * i] = sol[i];
            sol[2 * i + 1] = *it;
            Q.erase(it);
        }

        last += currLvl;
        currLvl *= 2;
    }

    printf("YES\n");
    for (int i = 1; i <= 2 * N - 1; i++) {
        printf("%d ", sol[i]);
    }
    printf("\n");
}

int main() {
    //freopen("inverseRmq.in", "r", stdin);
    read();
    solve();
    return 0;
}

