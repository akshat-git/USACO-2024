#include <bits/stdc++.h>
using namespace std;

int main(){
    int N, Q;
    cin >> N >> Q;

    vector<int> lineCountX(N*N, 0);
    vector<int> lineCountY(N*N, 0);
    vector<int> lineCountZ(N*N, 0);

    int fullX = 0, fullY = 0, fullZ = 0;

    auto increment_line = [&](vector<int> &lineCount, int idx, int &fullCount){
        int prev = lineCount[idx];
        lineCount[idx] = prev + 1;
        if (lineCount[idx] == N) {
            fullCount++;
        }
    };

    for (int i = 0; i < Q; i++) {
        int x,y,z;
        cin >> x >> y >> z;
        increment_line(lineCountX, y*N + z, fullX);
        increment_line(lineCountY, x*N + z, fullY);
        increment_line(lineCountZ, x*N + y, fullZ);

        cout << (fullX + fullY + fullZ) << "\n";
    }

    return 0;
}
