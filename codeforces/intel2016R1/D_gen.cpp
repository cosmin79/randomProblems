#include <cstdio>

int N = 50000;

int main() {
    freopen("D.in", "w", stdout);

    int currV = 1000000000;
    printf("%d\n", N);
    for (int i = N; i >= 1; i--) {
        printf("%d ", currV--);
    }
    printf("\n");
    return 0;
}