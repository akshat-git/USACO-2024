#include <bits/stdc++.h>
using namespace std;

static int mooid[26][26];
static string moos[650];

static int freq[650];
static int maxFreqArr[650];

inline int getMooID(char x, char y, char z) {
    if (y == z && x != y) {
        int A = x - 'a';
        int B = y - 'a';
        return mooid[A][B];
    }
    return -1;
}

int main() {
    int N, F;
    cin >> N >> F;
    string S; 
    cin >> S;

    int idx = 0;
    for (int A = 0; A < 26; A++) {
        for (int B = 0; B < 26; B++) {
            if (A != B) {
                mooid[A][B] = idx;
                moos[idx] = string({char('a'+A), char('a'+B), char('a'+B)});
                idx++;
            } else {
                mooid[A][B] = -1;
            }
        }
    }

    for (int i = 0; i + 2 < N; i++) {
        int m = getMooID(S[i], S[i+1], S[i+2]);
        if (m != -1) freq[m]++;
    }

    for (int i = 0; i < 650; i++) {
        maxFreqArr[i] = freq[i];
    }

    const char* str = S.c_str();

    for (int p = 0; p < N; p++) {
        char originalChar = str[p];
        for (char c = 'a'; c <= 'z'; c++) {
            if (c == originalChar) 
                continue; 

            static pair<int,int> changes[6];
            int changeCount = 0;

            auto process_substring = [&](int startIdx) {
                if (startIdx < 0 || startIdx + 2 >= N) return;
                char X = str[startIdx];
                char Y = str[startIdx+1];
                char Z = str[startIdx+2];

                if (p == startIdx) X = c;
                if (p == startIdx+1) Y = c;
                if (p == startIdx+2) Z = c;

                int oldMoo = getMooID(S[startIdx], S[startIdx+1], S[startIdx+2]);
                int newMoo = getMooID(X, Y, Z);

                if (oldMoo != -1) {
                    changes[changeCount++] = {oldMoo, -1};
                }
                if (newMoo != -1) {
                    changes[changeCount++] = {newMoo, +1};
                }
            };

            process_substring(p-2);
            process_substring(p-1);
            process_substring(p);

            static int deltaForMoo[6]; 
            map<int,int> aggregated;
            for (int i = 0; i < changeCount; i++) {
                aggregated[changes[i].first] += changes[i].second;
            }

            for (auto &kv : aggregated) {
                int mid = kv.first;
                int delta = kv.second;
                int newFreq = freq[mid] + delta;
                if (newFreq > maxFreqArr[mid]) {
                    maxFreqArr[mid] = newFreq;
                }
            }
        }
    }

    vector<string> result;
    for (int i = 0; i < 650; i++) {
        if (maxFreqArr[i] >= F) {
            result.push_back(moos[i]);
        }
    }

    sort(result.begin(), result.end());

    cout << (int)result.size() << "\n";
    for (auto &m : result) {
        cout << m << "\n";
    }

    return 0;
}
