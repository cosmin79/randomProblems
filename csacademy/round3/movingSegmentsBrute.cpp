#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int N;
struct segm {
    int x, y;
};
vector<segm> segms;

const long long INF_L = (1LL << 62);
const int INF = (1 << 30);

int minV = INF, maxV = -INF;

void read() {
    scanf("%d", &N);
    int x, y;
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &x, &y);
        segms.push_back({x, y});

        minV = min(minV, x);
        maxV = max(maxV, y);
    }
}

void solve() {
    long long result = INF;

    for (int y = minV; y <= maxV; y++) {
        long long curr = 0;
        for (int i = 0; i < N; i++) {
            if (segms[i].y < y) {
                curr += y - segms[i].y;
            } else if (segms[i].x > y) {
                curr += segms[i].x - y;
            }
        }

        result = min(result, curr);
    }
    
    printf("%lld\n", result);
}

int main() {
    freopen("movingSegments.in", "r", stdin);
    read();
    solve();
    return 0;
}