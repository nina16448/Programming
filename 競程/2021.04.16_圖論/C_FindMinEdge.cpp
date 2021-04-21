#include <bits/stdc++.h>
using namespace std;
#define len first
#define ID second
int n, m, a, b, w, k, r, rec;
priority_queue < pair <int, int> , vector < pair <int, int> >, greater<pair <int, int> > > pq[10000];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> a >> b >> w;
        pair <int, int> rec;
        rec.len = w;
        rec.ID = b;
        pq[a].push(rec);
    }
    cin >> k;
    while(k--){
        cin >> r;
        if(pq[r].empty()) cout << "-1\n";
        else 
            cout << pq[r].top().ID << " " << pq[r].top().len << "\n";
    }
    return 0;
}