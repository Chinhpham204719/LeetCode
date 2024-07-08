#include <vector>
#include <string>
#include <iostream>
using namespace std;

int getMaxRepetitions(string s1, int n1, string s2, int n2) {
    vector<int> rapport(102, -1);
    vector<int> rest(102, -1);
    int b = -1; 
    int posRest = 0;
    int rap = 0;
    int last = -1;
    rapport[0] = rest[0] = 0;

    for (int i = 1; i <= s2.size() + 1; i++) {
        for (int j = 0; j < s1.size(); j++) {
            if (s2[posRest] == s1[j]) {
                posRest++;
                if (posRest == s2.size()) {
                    rap++;
                    posRest = 0;
                }
            }
        }
        for (int k = 0; k < i; k++) {
            if (posRest == rest[k]) {
                b = k;
                last = i;
                break;
            }
        }
        rapport[i] = rap;
        rest[i] = posRest;
        if (b >= 0) break;
    }

    int interval = last - b;
    if (b >= n1) return rapport[n1] / n2;
    return ((n1 - b) / interval * (rapport[last] - rapport[b]) + rapport[(n1 - b) % interval + b]) / n2;
}

int main() {
    string s1 = "abc";
    int n1 = 4;
    string s2 = "ab";
    int n2 = 2;
    cout << getMaxRepetitions(s1, n1, s2, n2) << endl;
    return 0;
}
