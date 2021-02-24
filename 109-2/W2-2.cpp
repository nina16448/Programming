#include <bits/stdc++.h>
using namespace std;
vector <int> mapp[10000];
int visited[10000];
vector <int> stp;
int n, m, k, rec, a, b;

void DFS(int level){
    visited[level] = 1;
    stp.push_back(level);

    if(level == b){
        for(auto x: stp) cout << x << " ";
        cout << "\n";
        return;
    }
    
    for(auto x: mapp[level]){
        if(visited[x] == 1) continue;
        
        DFS(x);
        stp.pop_back();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    while(m--){
        cin >> a >> b;
        mapp[a].push_back(b);
        mapp[b].push_back(a);
    }
    cin >> k;
    
    while(k--){
        stp.clear();
        for(int i = 0; i < 10000; i++) visited[i] = 0;
        cin >> a >> b;
        DFS(a);

        if(visited[b] != 1) cout << "-1\n";
    }
    return 0;
}