#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

const int NMAX = 1055;
const int LMAX = 26;
int N;
string A;
bool mark[LMAX];

string transf(string& src, int ch1, int ch2) {
    string result;
    for (size_t i = 0; i < src.size(); i++) {
        if (src[i] - 'a' == ch1 || src[i] - 'a' == ch2) {
            result += src[i];
        }
    }

    return result;
}

bool valid(string& s) {
    for (size_t i = 1; i < s.size(); i++) {
        if (s[i] == s[i - 1]) {
            return false;
        }
    }

    return true;
}

int main() {
    //freopen("twoCharacters.in", "r", stdin);

    cin >> N >> A;

    for (int i = 0; i < N; i++) {
        mark[A[i] - 'a'] = true;
    }

    int result = 0;
    for (int fst = 0; fst < LMAX; fst++) {
        if (mark[fst]) {
            for (int snd = fst + 1; snd < LMAX; snd++) {
                if (mark[snd]) {
                    string rem = transf(A, fst, snd);

                    if (valid(rem)) {
                        result = max(result, (int)rem.size());
                    }
                }
            }
        }
    }

    printf("%d\n", result);
    return 0;
}

