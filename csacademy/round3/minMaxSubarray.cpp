#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> A;

void read() {
    scanf("%d", &N);
    int x;
    for (int i = 0; i < N; i++) {
        scanf("%d", &x);
        A.push_back(x);
    }
}

void solve() {
    int minV = A[0], maxV = A[0];
    for (int i = 1; i < N; i++) {
        minV = min(minV, A[i]);
        maxV = max(maxV, A[i]);
    }
    
    int result = N;
    for (int i = 1; i <= N; i++) {
        if (A[i] == minV) {
            for (int j = 1; j <= N; j++) {
                if (A[j] == maxV) {
                   result = min(result, abs(i - j) + 1); 
                }
            }
        }
    }
    
    printf("%d\n", result);
}

int main() {
    read();
    solve();
    return 0;
}