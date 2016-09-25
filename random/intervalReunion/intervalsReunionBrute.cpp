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

const int MAX_COORD = 10505;
bool covered[MAX_COORD], internal[MAX_COORD];

void read() {
    scanf("%d", &N);
    int x, y;
    for (int i = 0; i < N; i++) {
        scanf("%d%d", &x, &y);
        for (int coord = x; coord <= y; coord++) {
            covered[coord] = true;
            if (coord < y) {
                internal[coord] = true;
            }
        }
    }
}

vector<interval> solve() {
    vector<interval> result;
    
    int startInterv = -1;
    for (int coord = 0; coord <= MAX_COORD; coord++) {
        if (covered[coord]) {
            if (startInterv == -1) {
                startInterv = coord;
            } else if (!internal[coord - 1]) {
                // can't extend
                result.push_back({startInterv, coord - 1});
                startInterv = coord;
            }
        } else {
            if (startInterv != -1) {
                result.push_back({startInterv, coord - 1});
                startInterv = -1;
            }
        }
    }

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