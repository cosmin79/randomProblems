#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
const int NMAX = 55;
const int LMAX = 1055;
const int MOD = 1000000007;

int Q, N, subseqForPos[LMAX], r;
char A[LMAX];
string S;

int currSubSeq[LMAX], currSubSeqSize;

void read() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> S;
        
        for (auto& ch: S) {
            A[++r] = ch;
            subseqForPos[r] = i;
        }
    }
}

inline int hasBit(int mask, int bit) {
    return mask & (1 << (bit - 1));
}

inline bool atLeastOneFromEach() {
    int expected = 1, originalPos;
    for (int i = 1; i <= currSubSeqSize; i++) {
        originalPos = subseqForPos[currSubSeq[i]];
        if (originalPos > expected) {
            return false;
        } else if (originalPos == expected) {
            expected++;
        }
    }

    return expected == N + 1;
}

inline bool isPalindrom() {
    for (int i = 1; i <= currSubSeqSize / 2; i++) {
        if (A[currSubSeq[i]] != A[currSubSeq[currSubSeqSize - i + 1]]) {
            return false; 
        }
    }

    return true;
}

void solve() {
    int res = 0;
    for (int mask = 0; mask < (1 << r); mask++) {
        currSubSeqSize = 0;
        for (int i = 1; i <= r; i++) {
            if (hasBit(mask, i)) {
                currSubSeq[++currSubSeqSize] = i;
            }
        }

        if (atLeastOneFromEach() && isPalindrom()) {
            res++;
        }
    }

    printf("%d\n", res);
}

void clear() {
    r = 0;
}

int main() {
    freopen("palindromicString.in", "r", stdin);

    cin >> Q;
    while (Q--) {
        read();
        solve();

        clear();
    }
    return 0;
}
