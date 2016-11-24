#include <cstdio>
#include <string>
#include <sstream>
#include <iostream>
#include <set>
using namespace std;
const int NMAX = 105;
int N, P[NMAX];

set<char> vowels({'a', 'e', 'i', 'o', 'u', 'y'});
string line;

int getSylabes(string word) {
    int vwls = 0;
    for (auto& ch: word) {
        if (vowels.find(ch) != vowels.end()) {
            vwls++;
        }
    }

    return vwls;
}

int main() {
    //freopen("B.in", "r", stdin);

    getline(cin, line);
    stringstream ss(line);
    ss >> N;

    getline(cin, line);
    ss.str(line);
    ss.clear();
    for (int i = 1; i <= N; i++) {
        ss >> P[i];
    }

    for (int i = 1; i <= N; i++) {
        getline(cin, line);
        ss.str(line);
        ss.clear();

        string word;
        int sylabes = 0;
        while (ss >> word) {
            sylabes += getSylabes(word);
        }

        if (sylabes != P[i]) {
            printf("NO\n");
            return 0;
        }
    }

    printf("YES\n");
    return 0;
}