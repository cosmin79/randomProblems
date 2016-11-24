#include <cstdio>
#include <iostream>
using namespace std;

int type, HH, MM;
string s;

int diffNumbers(int x, int y) {
    int curr = (x % 10) != (y % 10);
    x /= 10; y /= 10;

    return curr + (x != y);
}

int main() {
    //freopen("A.in", "r", stdin);

    cin >> type >> s;
    HH = (s[0] - '0') * 10 + (s[1] - '0');
    MM = (s[3] - '0') * 10 + (s[4] - '0');

    int best = 100, resHH, resMM;
    if (type == 12) {
        for (int hh = 1; hh <= 12; hh++) {
            for (int mm = 0; mm <= 59; mm++) {
                int cost = diffNumbers(hh, HH) + diffNumbers(mm, MM);
                if (cost < best) {
                    best = cost;
                    resHH = hh; resMM = mm;
                }
            }
        }
    } else {
        for (int hh = 0; hh <= 59; hh++) {
            for (int mm = 0; mm <= 59; mm++) {
                int cost = diffNumbers(hh, HH) + diffNumbers(mm, MM);
                if (cost < best) {
                    best = cost;
                    resHH = hh; resMM = mm;
                }
            }
        }
    }

    printf("%02d:%02d\n", resHH, resMM);
    return 0;
}