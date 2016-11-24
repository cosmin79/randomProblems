#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
const int MOD = 1000000007;
const int NMAX = 1055;
int Q, M, N, res;
bool mark[NMAX][NMAX];

bool check() {
    for (int i = 3; i <= M; i++) {
        for (int j = 3; j <= N; j++) {
            int sum = 0;
            for (int l = i - 2; l <= i; l++) {
                for (int r = j - 2; r <= j; r++) {
                    if (l != i || r != j) {
                        sum += mark[l][r];
                    }
                }
            }
            if (sum < 1 || sum > 2) {
                return false;
            }

            mark[i][j] = 2 - sum;
        }
    }

    return true;
}

void fillFirstTwoCols(int row) {
    if (row == M + 1) {
        res += check();
        return ;
    }

    int currSum = 0;
    for (int i = row - 1; i >= row - 2; i--) {
        currSum += mark[i][1] + mark[i][2];
    }

    // (0, 0)
    mark[row][1] = mark[row][2] = false;
    fillFirstTwoCols(row + 1);

    if (currSum < 2) {
        // (1, 0)
        mark[row][1] = true; mark[row][2] = false;
        fillFirstTwoCols(row + 1);

        // (0, 1)
        mark[row][1] = false; mark[row][2] = true;
        fillFirstTwoCols(row + 1);
    }

    if (currSum == 0) {
        mark[row][1] = mark[row][2] = true;
        fillFirstTwoCols(row + 1);
    }
}

void fillFirstTwoRows(int col) {
    if (col == N + 1) {
        fillFirstTwoCols(3);
        return ;
    }

    int currSum = 0;
    for (int i = col - 1; i >= col - 2 && i >= 1; i--) {
        currSum += mark[1][i] + mark[2][i];
    }

    // (0, 0)
    mark[1][col] = mark[2][col] = false;
    fillFirstTwoRows(col + 1);

    if (currSum < 2) {
        // (1, 0)
        mark[1][col] = true; mark[2][col] = false;
        fillFirstTwoRows(col + 1);

        // (0, 1)
        mark[1][col] = false; mark[2][col] = true;
        fillFirstTwoRows(col + 1);
    }

    if (currSum == 0) {
        mark[1][col] = mark[2][col] = true;
        fillFirstTwoRows(col + 1);
    }
}

// This has beeen computed with the backtracking above
int sol[16][16] = 
{
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,36,78,156,270,612,1278,2268,5238,11124,19926,46332,98982,177876},
{0,0,0,78,140,238,372,766,1484,2526,5636,11662,20604,47398,100436,179718},
{0,0,0,156,238,356,510,956,1726,2820,6070,12236,21318,48500,101926,181596},
{0,0,0,270,372,510,684,1182,2004,3150,6540,12846,22068,49638,103452,183510},
{0,0,0,612,766,956,1182,1808,2758,4032,7750,14384,23934,52376,107062,187992},
{0,0,0,1278,1484,1726,2004,2758,3836,5238,9284,16246,26124,55438,110996,192798},
{0,0,0,2268,2526,2820,3150,4032,5238,6768,11142,18432,28638,58824,115254,197928},
{0,0,0,5238,5636,6070,6540,7750,9284,11142,16316,24406,35412,67630,126092,210798},
{0,0,0,11124,11662,12236,12846,14384,16246,18432,24406,33296,45102,79352,139846,226584},
{0,0,0,19926,20604,21318,22068,23934,26124,28638,35412,45102,57708,93990,156516,245286},
{0,0,0,46332,47398,48500,49638,52376,55438,58824,67630,79352,93990,135200,202654,296352},
{0,0,0,98982,100436,101926,103452,107062,110996,115254,126092,139846,156516,202654,275036,373662},
{0,0,0,177876,179718,181596,183510,187992,192798,197928,210798,226584,245286,296352,373662,477216}
};

int main() {
    freopen("academySurveillance.in", "r", stdin);

    /*for (int i = 3; i <= 15; i++) {
        for (int j = i; j <= 15; j++) {
            M = j; N = i;
            res = 0;
            fillFirstTwoRows(1);

            printf("ROW %d COL %d -> %d\n", i, j, res);
        }
    }*/

    scanf("%d", &Q);
    while (Q--) {
        scanf("%d%d", &M, &N);

        if (M < N) {
            std::swap(M, N);
        }

        res = 0;
        //fillFirstTwoRows(1);

        printf("%d\n", sol[N][M]);
    }
    return 0;
}
