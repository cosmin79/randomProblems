#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
const int NMAX = 55;
const int LMAX = 1055;
const int MOD = 1000000007;

int Q, N, pos[LMAX], r;
char A[LMAX];
string S;

int cnt[LMAX][LMAX][2][2];

void read() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> S;
        
        for (auto& ch: S) {
            A[++r] = ch;
            pos[r] = i;
        }
    }
}

inline void mod(int &x) {
    if (x >= MOD) {
        x -= MOD;
    }
    if (x < 0) {
        x += MOD;
    }
}

void solve() {
    for (int i = 1; i <= r; i++) {
        cnt[i][i][1][1] = 1;
    }

    for (int l = 2; l <= r; l++) {
        for (int i = 1; i <= r - l + 1; i++) {
            int lft = i, rght = i + l - 1;

            // take left, right
            if (A[lft] == A[rght]) {
                // try to make a new subseq just from lft, right
                // need to make sure there are no empty things in between
                if (pos[rght] - pos[lft] <= 1) {
                    cnt[lft][rght][1][1]++;
                }
                mod(cnt[lft][rght][1][1]);

                // the other option is attaching this to already existing
                // palindromic substring. need to make sure they were "properly" solved
                int solvedLft = pos[lft + 1] != pos[lft],
                    solvedRght = pos[rght - 1] != pos[rght];

                for (int nextLft = 1; nextLft >= solvedLft; nextLft--) {
                    for (int nextRght = 1; nextRght >= solvedRght; nextRght--) {
                        cnt[lft][rght][1][1] += cnt[lft + 1][rght - 1][nextLft][nextRght];
                        mod(cnt[lft][rght][1][1]);
                    }
                }
            }

            for (int lftState = 0; lftState < 2; lftState++) {
                for (int rghtState = 0; rghtState < 2; rghtState++) {
                    // look at all 4 cases
                    if (pos[lft] == pos[lft + 1] && pos[rght] == pos[rght - 1]) {
                        // neither left, nor right are on boundary
                        cnt[lft][rght][lftState][rghtState] += cnt[lft + 1][rght][lftState][rghtState];
                        mod(cnt[lft][rght][lftState][rghtState]);

                        cnt[lft][rght][lftState][rghtState] += cnt[lft][rght - 1][lftState][rghtState];
                        mod(cnt[lft][rght][lftState][rghtState]);

                        cnt[lft][rght][lftState][rghtState] -= cnt[lft + 1][rght - 1][lftState][rghtState];
                    } else if (pos[lft] != pos[lft + 1] && pos[rght] == pos[rght - 1]) {
                        // left on boundary, right not on boundary
                        if (!lftState) {
                            cnt[lft][rght][lftState][rghtState] += cnt[lft + 1][rght][1][rghtState];
                            mod(cnt[lft][rght][lftState][rghtState]);
                        }

                        cnt[lft][rght][lftState][rghtState] += cnt[lft][rght - 1][lftState][rghtState];
                        mod(cnt[lft][rght][lftState][rghtState]);

                        if (!lftState) {
                            cnt[lft][rght][lftState][rghtState] -= cnt[lft + 1][rght - 1][1][rghtState];
                        }
                    } else if (pos[lft] == pos[lft + 1] && pos[rght] != pos[rght - 1]) {
                        // left not on boundary, right on boundary
                        cnt[lft][rght][lftState][rghtState] += cnt[lft + 1][rght][lftState][rghtState];
                        mod(cnt[lft][rght][lftState][rghtState]);

                        if (!rghtState) {
                            cnt[lft][rght][lftState][rghtState] += cnt[lft][rght - 1][lftState][1];
                            mod(cnt[lft][rght][lftState][rghtState]);
                        }

                        if (!rghtState) {
                            cnt[lft][rght][lftState][rghtState] -= cnt[lft + 1][rght - 1][lftState][1];
                        }
                    } else {
                        // both left and right are on boundary
                        if (!lftState) {
                            cnt[lft][rght][lftState][rghtState] += cnt[lft + 1][rght][1][rghtState];
                            mod(cnt[lft][rght][lftState][rghtState]);
                        }

                        if (!rghtState) {
                            cnt[lft][rght][lftState][rghtState] += cnt[lft][rght - 1][lftState][1];
                            mod(cnt[lft][rght][lftState][rghtState]);
                        }

                        if (!lftState && !rghtState) {
                            cnt[lft][rght][lftState][rghtState] -= cnt[lft + 1][rght - 1][1][1];   
                        }
                    }


                    mod(cnt[lft][rght][lftState][rghtState]);
                    /*printf("LEFT: %d, RIGHT: %d, lftState: %d, rghtState: %d, RES: %d\n", 
                        lft, rght, lftState, rghtState, cnt[lft][rght][lftState][rghtState]);*/
                }
            }
        }
    }

    printf("%d\n", cnt[1][r][1][1]);
}

void clear() {
    r = 0;
    memset(cnt, 0, sizeof(cnt));
    memset(pos, 0, sizeof(pos));
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
