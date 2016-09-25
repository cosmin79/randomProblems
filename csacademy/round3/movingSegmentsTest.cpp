#include <cstdio>
#include <ctime>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main() {
    srand(time(0));
    freopen("movingSegments.in", "w", stdout);

    int N = rand() % 10 + 1;
    printf("%d\n", N);

    for (int i = 1; i <= N; i++) {
        int start = rand() % 15;
        int l = rand() % 8;
        printf("%d %d\n", start, start + l);
    }

    return 0;
}