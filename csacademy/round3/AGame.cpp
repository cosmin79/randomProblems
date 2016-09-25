#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

const int NMAX = 100505;
int N;
char A[NMAX];

void read() {
    scanf("%d\n", &N);
    scanf("%s", A + 1);
}

void solve() {
    vector<int> piles;
    int numsA = 0, currPile = 0;
    for (int i = 1; i <= N; i++) {
        if (A[i] == 'A') {
            numsA++;
            if (currPile) {
                piles.push_back(currPile);
                currPile = 0;
            }
        } else {
            currPile++;
        }
    }
    if (currPile) {
        piles.push_back(currPile);
    }
    
    int pilesXor = 0;
    for (auto pile: piles) {
        pilesXor ^= pile;
    }
    
    // 1st wins
    if (pilesXor) {
        if (numsA % 2 == 0) {
            printf("-1\n");
        } else {
            printf("A\n");
        }
    } else {
        if (numsA % 2 == 0) {
            printf("-1\n");
        } else {
            printf("B\n");
        }
    }
}

int main() {
    read();    
    solve();
    return 0;
}