#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> nums, bestSubset;

void read() {
    scanf("%d", &N);
    int x;
    for (int i = 0; i < N; i++) {
        scanf("%d", &x);
        nums.push_back(x);
    }
}

void solve() {
    sort(nums.begin(), nums.end());
    bestSubset.assign(N, 1);
    
    int result = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] % nums[j] == 0) {
                bestSubset[i] = max(bestSubset[i], 1 + bestSubset[j]);
            }
        }
        
        result = max(result, bestSubset[i]);
    }
    
    printf("%d\n", result);
}

int main() {
    read();
    solve();
    return 0;
}