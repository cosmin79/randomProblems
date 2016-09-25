#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;
struct interval {
    int x, y;

    bool operator < (const interval& other) const {
        return x < other.x;
    }
};

int N;
vector<interval> intervals;

void read() {
    scanf("%d", &N);
    intervals.reserve(N);
    int x, y;
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &x, &y);
        intervals.push_back({x, y});
    }
}

vector<interval> solve() {
    assert(intervals.size() > 0);

    vector<interval> result;
    sort(intervals.begin(), intervals.end());
    interval currInterval = intervals[0];
    int currStart = intervals[0].x, largestCovered = intervals[0].y;
    for (size_t i = 1; i < intervals.size(); i++) {
        if (intervals[i].x <= currInterval.y) {
            currInterval.y = max(currInterval.y, intervals[i].y);
        } else {
            result.push_back(currInterval);
            currInterval = intervals[i];
            currStart = intervals[i].x;
        }
    }
    result.push_back(currInterval);

    return result;
}

void printIntervals(vector<interval>& intervals) {
    for (auto& interv: intervals) {
        printf("%d %d\n", interv.x, interv.y);
    }
}

int main() {
    freopen("intervalsReunion.in", "r", stdin);
    read();
    vector<interval> result = solve();
    printIntervals(result);
    return 0;
}