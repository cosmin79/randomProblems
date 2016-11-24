#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

const int NMAX = 100505;
int N, A[NMAX], aib[NMAX], nxtPos[NMAX];
unordered_map<int, int> lastAp;
unordered_set<int> solved;

int lsb(int x) {
    return x & -x;
}

void update(int pos, int v) {
    for (; pos <= N; pos += lsb(pos)) {
        aib[pos] += v;
    }
}

int sum(int  pos) {
    int result = 0;
    for ( ; pos ; pos -= lsb(pos)) {
        result += aib[pos];
    }
    
    return result;
}

void read() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
}

void solve() {
    for (int i = N; i >= 1; i--) {
        auto it = lastAp.find(A[i]);
        if (it != lastAp.end()) {
            nxtPos[i] = it -> second;
        }
        
        lastAp[A[i]] = i;
    }
    
    long long result = 0;
    for (int i = 1; i <= N; i++) {
        // already matched
        if (solved.find(A[i]) != solved.end()) {
            continue ;
        }
        
        int otherPos = nxtPos[i];
        result += (otherPos - i - 1) - (sum(otherPos) - sum(i));
        solved.insert(A[i]);
        update(otherPos, 1);
    }
    
    printf("%lld\n", result);
}

int main() {
    read();
    solve();
    return 0;
}