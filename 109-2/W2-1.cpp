#include <bits/stdc++.h>
using namespace std;
vector <int> mapp[10000];
int visited[10000];
int n, m, k, rec, a, b;

void DFS(int level){
    visited[level] = 1;

    if(level == b)
        return;
    
    for(auto x: mapp[level]){
        if(visited[x]) continue;
        DFS(x);
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
        for(int i = 0; i < 10000; i++) visited[i] = 0;
        cin >> a >> b;
        DFS(a);

        if(visited[b]) cout << "Yes\n";
        else cout << "No\n";
    }
    return 0;
}