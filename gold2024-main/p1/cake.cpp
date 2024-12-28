#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T; 
    cin >> T;
    while (T--) {
        int N; 
        cin >> N;
        deque<long long> cakes;

        for (int i = 0; i < N; i++) {
            long long cake; cin >> cake;
            cakes.push_back(cake);
        }

        long long bessie_sum = 0, elsie_sum = 0;
        bool bessieTurn = true;

        while (cakes.size() > 2) {
            if (bessieTurn) {
                long long max_sum = -1;
                int max_index = -1;
                for (int i = 1; i < (int)cakes.size() - 2; i++) {
                    long long current_sum = cakes[i] + cakes[i + 1];
                    if (current_sum > max_sum) {
                        max_sum = current_sum;
                        max_index = i;
                    }
                }

                if (max_index != -1) {
                    cout << "Bessie merges " << cakes[max_index] << " and " << cakes[max_index + 1] << "\n";
                    cakes[max_index] += cakes[max_index + 1];
                    cakes.erase(cakes.begin() + max_index + 1);
                }
            } else {
                if (cakes.front() >= cakes.back()) {
                    elsie_sum += cakes.front();
                    cout << "Elsie picks " << cakes.front() << " from the front\n";
                    cakes.pop_front();
                } else {
                    elsie_sum += cakes.back();
                    cout << "Elsie picks " << cakes.back() << " from the back\n";
                    cakes.pop_back();
                }
            }
            bessieTurn = !bessieTurn; // Alternate turns
        }

        if (cakes.size() == 2) {
            cout << "Bessie eats the last two cakes: " << cakes.front() << " and " << cakes.back() << "\n";
            bessie_sum += cakes.front() + cakes.back();
        } else {
            cout << "Bessie eats the last cake: " << cakes.front() << "\n";
            bessie_sum += cakes.front();
        }

        cout << "Final Bessie Sum: " << bessie_sum << ", Final Elsie Sum: " << elsie_sum << "\n";
        cout << bessie_sum << " " << elsie_sum << "\n";
    }

    return 0;
}
