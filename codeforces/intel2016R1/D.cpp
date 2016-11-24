#include <cstdio>
#include <unordered_map>
#include <vector>
#include <cstring>
using namespace std;

const int NMAX = 50505;
const int LMAX = 1600505;
int N, A[NMAX];

vector<int> G[NMAX];
int currIdx;
unordered_map<int, int> allValues;
vector<int> newValues;

int L[NMAX];
bool mark[NMAX];
vector<int> R;

void read() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }

    // should be enough
    for (int i = 1; i <= N; i++) {
        G[i].reserve(30);
    }
}

inline int bit(int idx) {
    return 1 << (idx - 1);
}

inline bool hasBit(int mask, int idx) {
    return mask & bit(idx);
}

void findCandidates(int x, int maxV, vector<int>& result) {
    int fstBit;
    for (int i = 30; i >= 1; i--) {
        if (hasBit(x, i)) {
            fstBit = i;
            break ;
        }
    }

    int curr = 0;
    for (int i = fstBit; i >= 1; i--) {
        curr = (curr << 1) + hasBit(x, i);
        if (curr > maxV) {
            break; 
        }

        result.push_back(curr);
    }
}

void clearPrevIter() {
    allValues.clear();
    newValues.clear();
    for (int i = 1; i <= N; i++) {
        G[i].clear();
    }
    currIdx = N;
}

bool pairup(int x) {
    mark[x] = true;
    for (auto& y: G[x]) {
        if (!R[y] || (!mark[R[y]] && pairup(R[y]))) {
            L[x] = y;
            R[y] = x;
            return true;
        }
    }

    return false;
}

bool canMatch() {
    memset(L, 0, sizeof(L));
    R.assign(currIdx + 1, 0);

    bool improve = true;
    int currMatches = 0;
    while (improve) {
        improve = false;
        memset(mark, false, sizeof(mark));

        for (int i = 1; i <= N; i++) {
            if (!L[i] && pairup(i)) {
                improve = true;
                currMatches++;
            }
        }
    }

    return currMatches == N;
}

bool check(int maxV) {
    vector<int> currCandidates;
    currCandidates.reserve(30);
    clearPrevIter();

    // cstr graph
    for (int i = 1; i <= N; i++) {
        currCandidates.clear();
        findCandidates(A[i], maxV, currCandidates);

        for (auto& cand: currCandidates) {
            auto it = allValues.find(cand);
            int matchIdx;
            if (it == allValues.end()) {
                allValues[cand] = ++currIdx;
                newValues.push_back(cand);
                matchIdx = currIdx;
            } else {
                matchIdx = it -> second;
            }

            G[i].push_back(matchIdx);
        }
    }

    return canMatch();
}

int bSearch() {
    int i, step = (1 << 30);

    for (i = 0; step; step >>= 1) {
        if (!check(i + step)) {
            i += step;
        }
    }

    return ++i;
}

void solve() {
    int maxElem = bSearch();

    // populate solution
    check(maxElem);
    for (int i = 1; i <= N; i++) {
        if (i > 1) {
            printf(" ");
        }
        printf("%d", newValues[L[i] - N - 1]);
    }
    printf("\n");
}

int main() {
    freopen("D.in", "r", stdin);

    read();
    solve();
    return 0;
}