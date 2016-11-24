#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <map>
using namespace std;

struct segment {
    int x, y;

    bool operator < (const segment& other) const {
        return y < other.y;
    }
};

int N, M, K;
unordered_map<int, vector<segment>> trains;

void read() {
    scanf("%d%d%d", &N, &M, &K);
    int r, x, y;
    for (int i = 1; i <= K; i++) {
        scanf("%d%d%d", &r, &x, &y);
        trains[r].push_back({x, y});
    }
}

enum event {
    START, END
};

long long sumIntersection(vector<segment>& segments) {
    sort(segments.begin(), segments.end());
    
    map<int, vector<event>> events;
    for (auto& segm: segments) {
        events[segm.x].push_back(START);
        events[segm.y].push_back(END);
    }

    vector<int> pts;
    for (auto it = events.begin(); it != events.end(); it++) {
        pts.push_back(it -> first);
    }

    int prevValue = pts[0] - 1, cntUp = 0, result = 0;
    for (size_t i = 0; i < pts.size(); i++) {
        if (cntUp && pts[i] - prevValue > 1) {
            result += pts[i] - prevValue - 1;
        }

        for (auto &v: events[pts[i]]) {
            if (v == START) {
                cntUp++;
            }
        }

        // adding Y = pts[i]
        if (cntUp) {
            result++;
        }

        for (auto &v: events[pts[i]]) {
            if (v == END) {
                cntUp--;
            }
        }

        prevValue = pts[i];
    }

    return result;
}

void solve() {
    long long result = 0;
    for (auto it = trains.begin(); it != trains.end(); it++) {
        vector<segment> trainsRow = it -> second;
        result += sumIntersection(trainsRow);
    }

    printf("%lld\n", 1LL * N * M - result);
}

int main() {
    freopen("gridlandMetro.in", "r", stdin);

    read();
    solve();
    return 0;
}

