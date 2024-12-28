#include <bits/stdc++.h>
using namespace std;

struct Fenw {
    int n;
    vector<int> fenw;
    Fenw(int n):n(n), fenw(n+1,0){}
    void update(int i,int v){
        for(;i<=n;i+=i&(-i)) fenw[i]+=v;
    }
    int query(int i){
        int s=0;
        for(;i>0;i-=i&(-i)) s+=fenw[i];
        return s;
    }
    int rangeQuery(int l,int r){
        return query(r)-query(l-1);
    }
};

struct Interval {
    long long l, r;
    int t;
};

int main(){
    int T; 
    cin >> T;
    while(T--){
        int N,K; 
        cin >> N >> K;
        vector<long long> X(N);
        for (int i=0; i<N; i++) cin >> X[i];
        sort(X.begin(), X.end());

        vector<Interval> intervals(K);
        for(int i=0; i<K; i++){
            cin >> intervals[i].l >> intervals[i].r >> intervals[i].t;
        }
        
        sort(intervals.begin(), intervals.end(), [](const Interval &A, const Interval &B){
            if(A.r == B.r) return A.l < B.l;
            return A.r < B.r;
        });

        Fenw fenw(N);
        set<int> unchosen;
        for (int i=1; i<=N; i++)
            unchosen.insert(i);

        for (auto &interval : intervals) {
            long long l = interval.l, r = interval.r;
            int t = interval.t;

            int L = (int)(lower_bound(X.begin(), X.end(), l) - X.begin())+1;
            int R = (int)(upper_bound(X.begin(), X.end(), r) - X.begin());

            if(L > R) {
                continue;
            }

            int chosenCount = fenw.rangeQuery(L,R);
            if (chosenCount < t) {
                int need = t - chosenCount;
                auto it = unchosen.upper_bound(R);
                while (need > 0 && it != unchosen.begin()) {
                    --it;
                    int idx = *it;
                    if (idx < L) 
                      break; 
                    fenw.update(idx,1);
                    unchosen.erase(it);
                    need--;
                    it = unchosen.upper_bound(R); 
                }
            }
        }

        int chosenCount = fenw.query(N);
        int cutCount = N - chosenCount;
        cout << cutCount << "\n";
    }

    return 0;
}
