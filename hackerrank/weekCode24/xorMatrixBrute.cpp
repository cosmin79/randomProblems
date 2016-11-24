#include <cstdio>
#include <cstring>

const int NMAX = 100505;
int M, A[2][NMAX];
long long N;

void read() {
    scanf("%d%lld", &M, &N);
    for (int i = 0; i < M; i++) {
        scanf("%d", &A[0][i]);
    }
}

void solve() {
    int nextCol;
    for (long long i = 1; i < N; i++) {
        for (int j = 0; j < M; j++) {
            nextCol = (j + 1) % M;
            A[i & 1][j] = A[(i - 1) & 1][j] ^ A[(i - 1) & 1][nextCol];
        }
    }

    for (int i = 0; i < M; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", A[(N - 1) & 1][i]);
    }
    printf("\n");
}

int main() {
    freopen("xorMatrix.in", "r", stdin);

    read();
    solve();
    return 0;
}