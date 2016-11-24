#include <cstdio>
#include <iostream>

using namespace std;

int tests, A, B;

long long get(int N) {
    if (N <= 1) {
        return N;
    }
    
    int largestOdd = N & 1 ? N : N - 1;
    long long sum = 1LL * (largestOdd / 2 + 1) * (largestOdd / 2 + 1);
    return sum + get(N >> 1);
}

int main() {
    scanf("%d", &tests);
    while (tests--) {
        scanf("%d%d", &A, &B);
        printf("%lld\n", get(B) - get(A - 1));
    }
    return 0;
}