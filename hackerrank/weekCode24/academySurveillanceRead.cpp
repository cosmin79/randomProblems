#include <cstdio>
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

const int NMAX = 16;
string rowString, colString, arrowString;
int r, c, v;

int res[NMAX][NMAX];

int main() {
    freopen("academyPrecompute.in", "r", stdin);

    for (int i = 3; i <= 15; i++) {
        for (int j = i; j <= 15; j++) {
            cin >> rowString >> r >> colString >> c >> arrowString >> v;

            res[i][j] = res[j][i] = v;
            assert (r == i);
            assert (c == j);
        }
    }

    // serialize
    printf("{\n");
    for (int i = 0; i < NMAX; i++) {
        printf("{");
        for (int j = 0; j < NMAX; j++) {
            if (j > 0) {
                printf(",");
            }
            printf("%d", res[i][j]);
        }

        printf("}");
        if (i < NMAX - 1) {
            printf(",");
        }
        printf("\n");
    }
    printf("}\n");
    return 0;
}