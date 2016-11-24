#include <ctime>
#include <cstdlib>
#include <cstdio>

int main() {
    freopen("recordEpisodes.in", "w", stdout);

    srand(time(0));
    int Q = rand() % 100 + 1;
    printf("%d\n", Q);
    for (int i = 1; i <= Q; i++) {
        int N = rand() % 100 + 1;
        printf("%d\n", N);

        for (int i = 1; i <= N; i++) {
            int start1 = rand() % 2000, start2 = start1 + rand() % 1000;
            printf("%d %d %d %d\n", start1, start1 + rand() % 8000, start2, start2 + rand() % 8000);
        }
    }
    return 0;
}