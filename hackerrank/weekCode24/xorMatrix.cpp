#include <cstdio>
#include <cstring>

const int NMAX = 100505;
int M, A[NMAX], aux[NMAX];
long long N;

void read() {
    scanf("%d%lld", &M, &N);
    for (int i = 0; i < M; i++) {
        scanf("%d", &A[i]);
    }
}

void move(int A[], long long powTwoSteps) {
    int modSteps = powTwoSteps % M, currCol = modSteps;
    for (int i = 0; i < M; i++) {
        aux[i] = A[i] ^ A[currCol];
        currCol++;
        if (currCol >= M) {
            currCol -= M;
        }
    }
    memcpy(A, aux, sizeof(aux));
}

void solve() {
    N--;

    for (int i = 60; i >= 0; i--) {
        if (N & (1LL << i)) {
            move(A, 1LL << i);
        }
    }

    for (int i = 0; i < M; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", A[i]);
    }
    printf("\n");
}

int main() {
    freopen("xorMatrix.in", "r", stdin);

    read();
    solve();
    return 0;
}
