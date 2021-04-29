#include <bits/stdc++.h>
using namespace std;
int n, m, u, v, s, t;
int stp[30000];
queue <int> qu;
vector <int> mapp[30000];

void BFS(int level){
    for(auto x: mapp[level]){
        if(stp[x] != 0) continue;

        qu.push(x);
        stp[x] = stp[level] + 1;
    }
    qu.pop();
    if(qu.empty()) return;
    BFS(qu.front());
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        cin >> u >> v;
        mapp[u].push_back(v);
        mapp[v].push_back(u);
    }

    cin >> s >> t;
    qu.push(s);
    stp[s] = 1;
    BFS(s);
    
    cout << stp[t] - 1 << "\n";
    return 0;
}