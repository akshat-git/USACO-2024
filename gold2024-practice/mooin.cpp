#include <bits/stdc++.h>
using namespace std;

bool isValidMoo(const string &s, int start) {
    if ((start + 2) >= s.length()) 
        return false;
    return (s[start] != s[start + 1]) && (s[start + 1] == s[start + 2]); // mock moo basically
}

int main() {
    int N, F;
    cin >> N >> F;
    string contest;
    cin >> contest;

    set<string> moos; //moo storage 
    unordered_map<string, int> mooCount; // freq tracker
    
    for (int i = 0; i < N - 2; i++) {
        if (isValidMoo(contest, i)) {
            string moo = contest.substr(i, 3);
            mooCount[moo]++;
        }
    }

    for (int i = 0; i < N; i++) {
        char originalChar = contest[i]; // char change check now
        for (char c = 'a'; c <= 'z'; c++) {
            if (c == originalChar) continue;

            contest[i] = c; // make change
            for (int j = max(0, i - 2); j <= min(N - 3, i); j++) {
                if (isValidMoo(contest, j)) {
                    string moo = contest.substr(j, 3);
                    //mooCount[moo]++;
                }
            }
            contest[i] = originalChar; // restore
        }
    }

    for (const auto &entry : mooCount) {
        if (entry.second >= F) {
            moos.insert(entry.first);
        }
    }
    cout << moos.size() << endl;
    for (const string &moo : moos) {
        cout << moo << endl;
    }

    return 0;
}