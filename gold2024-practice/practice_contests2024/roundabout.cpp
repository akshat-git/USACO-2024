#include <bits/stdc++.h>
using namespace std;

long long repeated_digit(int d, int count) {
    long long result = 0;
    for (int i=0; i<count; i++) {
        result = result*10 + d;
    }
    return result;
}

long long base_differences(int x) {
    if (x <= 2) return 0;
    long long p=1;
    for (int i=2; i<x; i++) 
        p *= 10;
    return (5*(p-1))/9 + base_differences(x - 1);
}


long long chunk_for_leading(int x, int leading) {
    if ((leading <= 4) || (x == 2)) 
        return 0;
    long long p = 1;
    for (int i = 2; i < x; i++)
        p *= 10;
    return p * 5;
}

long long f(long long N) {
    if (N < 2) return 0;
    if (N < 5) return 0;

    string s = to_string(N);
    int x = (int)s.size();

    long long count_diff = base_differences(x);
    long long four_threshold = repeated_digit(4, x);
    if (N > four_threshold) {
        count_diff += (N - four_threshold);
    }

    int leading = s[0]-'0';
    if (leading > 4) {
        count_diff = base_differences(x + 1);
    }

    return count_diff;
}

int main() {
    int T; 
    cin >> T;
    while (T--) {
        long long N; 
        cin >> N;
        cout << f(N) << "\n";
    }

    return 0;
}
