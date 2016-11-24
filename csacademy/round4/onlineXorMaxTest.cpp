#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int NMAX = 100505;

int N, A[NMAX], P[NMAX];

int main() {
    freopen("onlineXorMax.in", "w", stdout);

    srand(time(0));
    N = 100000;
    for (int i = 1; i <= N; i++) {
        A[i] = rand() % 1000000000;
        P[i] = i;
    }
    random_shuffle(P + 1, P + N + 1);

    printf("%d\n", N);
    for (int i = 1; i <= N; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");

    for (int i = 1; i <= N; i++) {
        printf("%d ", P[i]);
    }
    printf("\n");
    return 0;
}