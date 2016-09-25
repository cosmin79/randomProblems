#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
const int NMAX = 10000;
const int MAX_COORD = 10000;
const int MAX_LENGTH = 50;
int N;

int main() {
    freopen("intervalsReunion.in", "w", stdout);
    srand(time(0));

    N = rand() % NMAX + 1;
    printf("%d\n", N);
    for (int i = 1; i <= N; i++) {
        int st = rand() % MAX_COORD;
        int maxL = min(MAX_LENGTH + 1, MAX_COORD - st + 1);
        printf("%d %d\n", st, st + maxL);
    }
    return 0;
}