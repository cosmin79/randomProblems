#include <cstdio>
#include <cstring>
const int NMAX = 100505;
const int VMAX = 50505;

bool mark[VMAX], curr[VMAX];
int N, vals[VMAX], r, newVals[VMAX];

int main() {
    freopen("iterate.in", "r", stdin);

    scanf("%d", &N);
    int x, noValues = 0;
    for (int i = 1; i <= N; i++) {
        scanf("%d", &x);
        curr[x] = true;
    }

    for (int i = 1; i < VMAX; i++) {
        if (curr[i]) {
            vals[++noValues] = i;
        }
    }

    int iterations = 0;
    while (noValues > 1) {
        r = noValues; noValues = 0;

        for (int i = 1; i <= r; i++) {
            curr[vals[i]] = true;
        }

        for (int i = 1; i <= r; i++) {
            for (int target = 1; target < VMAX - vals[i]; target++) {
                if (curr[target + vals[i]] && !mark[target]) {
                    mark[target] = true;
                    newVals[++noValues] = target;
                }
            }
        }

        memset(curr, false, sizeof(curr));
        memset(mark, false, sizeof(mark));
        memcpy(vals, newVals, sizeof(newVals));

        iterations++;
    }

    printf("%d\n", iterations + 1);

    return 0;
}