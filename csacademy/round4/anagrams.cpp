#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <algorithm>
using namespace std;

int N;
string s;
unordered_map<string, int> cnt;

int main() {
    cin >> N;
    int result = 0;
    for (int i = 0; i < N; i++) {
        cin >> s;
        sort(s.begin(), s.end());
        cnt[s]++;
        
        result = max(result, cnt[s]);
    }
    
    cout << result << "\n";
    return 0;
}