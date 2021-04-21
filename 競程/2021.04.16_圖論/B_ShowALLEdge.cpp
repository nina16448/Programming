#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, k, r;
vector <int> mapp[10000];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        cin >> a >> b;
        mapp[a].push_back(b);
        mapp[b].push_back(a);
    }
    cin >> k;
    while(k--){
        cin >> r;
        sort(mapp[r].begin(), mapp[r].end());
        if(mapp[r].empty()) cout << "-1\n";
        else for(auto x: mapp[r]) cout << x << " ";
        cout << "\n";
    }
    return 0;
}