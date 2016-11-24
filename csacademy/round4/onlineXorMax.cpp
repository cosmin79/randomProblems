#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int NMAX = 100505;
const int NO_BITS = 30;
int N, A[NMAX], P[NMAX];

int S[NMAX], whichComponent[NMAX], res[NMAX];
bool valid[NMAX], sHasBit[NMAX][NO_BITS + 1];

struct trieNode {
    trieNode* children[2];

    trieNode() {
        memset(children, 0, sizeof(children));
    }

    ~trieNode() {
        for (int i = 0; i < 2; i++) {
            if (children[i]) {
                delete children[i];
            }
        }
    }
};

struct component {
    int best, l, r;

    trieNode* root;

    component(int pos) {
        best = A[pos];
        l = r = pos;
        root = new trieNode();
    }

    ~component() {
        delete root;
    }

    int size() {
        return r - l + 1;
    }
};
component* comps[NMAX];

void read() {
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &A[i]);
    }
    for (int i = 1; i <= N; i++) {
        scanf("%d", &P[i]);
    }
}

inline int bit(int pos) {
    return 1 << (pos - 1);
}

inline bool hasBit(int mask, int pos) {
    return mask & bit(pos);
}

void insertTrie(trieNode* node, int idx) {
    int bitV;
    for (int i = NO_BITS; i >= 1; i--) {
        bitV = sHasBit[idx][i];
        if (node -> children[bitV] == 0) {
            node -> children[bitV] = new trieNode();
        }
        node = node -> children[bitV];
    }
}

void prepare() {
    for (int i = 1; i <= N; i++) {
        S[i] = S[i - 1] ^ A[i];
    }

    for (int i = 0; i <= N; i++) {
        for (int b = NO_BITS; b >= 1; b--) {
            sHasBit[i][b] = hasBit(S[i], b);
        }
    }
}

int getBest(trieNode* node, int idx) {
    int bitV, currBest = 0;
    for (int i = NO_BITS; i > 0; i--) {
        bitV = sHasBit[idx][i];
        currBest <<= 1;

        if (node -> children[bitV ^ 1]) {
            currBest++;
            node = node -> children[bitV ^ 1];
        } else {
            node = node -> children[bitV];
        }
    }

    return currBest;
}

void merge(int comp1, int comp2) {
    if (comp1 == comp2) {
        return ;
    }

    // will merge comp1 into comp2
    if (comps[comp1] -> size() > comps[comp2] -> size()) {
        swap(comp1, comp2);
    }
    comps[comp2] -> best = max(comps[comp2] -> best, comps[comp1] -> best);

    // combinations between subsequences
    for (int i = comps[comp1] -> l - 1; i <= comps[comp1] -> r; i++) {
        comps[comp2] -> best = max(comps[comp2] -> best, 
            getBest(comps[comp2] -> root, i));
    }
    // update trie
    for (int i = comps[comp1] -> l - 1; i <= comps[comp1] -> r; i++) {
        insertTrie(comps[comp2] -> root, i);
    }

    // update tracking information
    for (int i = comps[comp1] -> l; i <= comps[comp1] -> r; i++) {
        whichComponent[i] = comp2;
    }
    // update [l, r] interval
    comps[comp2] -> l = min(comps[comp1] -> l, comps[comp2] -> l);
    comps[comp2] -> r = max(comps[comp1] -> r, comps[comp2] -> r);

    //delete comps[comp1];
}

void solve() {
    prepare();

    int bestSoFar = 0;
    for (int i = N; i >= 1; i--) {
        int currPos = P[i];
        // setup component of size 1
        comps[currPos] = new component(currPos);
        insertTrie(comps[currPos] -> root, currPos);
        insertTrie(comps[currPos] -> root, currPos - 1);
        whichComponent[currPos] = currPos;
        valid[currPos] = true;

        // attempt to merge with neighbor components
        if (valid[currPos - 1]) {
            merge(whichComponent[currPos - 1], whichComponent[currPos]);
        }
        if (valid[currPos + 1]) {
            merge(whichComponent[currPos + 1], whichComponent[currPos]);
        }

        // update curr best
        bestSoFar = max(bestSoFar, comps[whichComponent[currPos]] -> best);
        res[i] = bestSoFar;
    }

    for (int i = 1; i <= N; i++) {
        printf("%d\n", res[i]);
    }
}

int main() {
    freopen("onlineXorMax.in", "r", stdin);

    read();
    solve();
    return 0;
}
