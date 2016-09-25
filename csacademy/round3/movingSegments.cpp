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

vector<int> endpoints;
unordered_map<int, int> startEvent, endEvent;

void read() {
    scanf("%d", &N);
    int x, y;
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &x, &y);
        segms.push_back({x, y});
        
        endpoints.push_back(x); startEvent[x]++;
        endpoints.push_back(y); endEvent[y]++;
    }
}

void solve() {
    sort(endpoints.begin(), endpoints.end());
    endpoints.resize(unique(endpoints.begin(), endpoints.end()) - endpoints.begin());
    
    int numLeft = 0, numRight = N, prevEndpoint = endpoints[0] - 1;
    long long curr = 0;
    // pos: endpoints[i] - 1
    for (auto& segment: segms) {
        curr += segment.x - prevEndpoint;
    }
    
    long long result = curr;
    for (size_t i = 0; i < endpoints.size(); i++) {
        curr += numLeft * (endpoints[i] - prevEndpoint);
        curr -= numRight * (endpoints[i] - prevEndpoint);
        
        numLeft += endEvent[endpoints[i]];
        numRight -= startEvent[endpoints[i]];
        
        prevEndpoint = endpoints[i];
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