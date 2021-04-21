#include <bits/stdc++.h>
using namespace std;
int n, m, x, y, a, b, rec;
vector <int> mapp[100000];
int visited[100];

void DFS(int level){
    visited[level] = 1;
    if(level == b) return;

    for(auto x: mapp[level]){
        if(visited[x]) continue;
        DFS(x);
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;

    for(int i = 0; i < m; i++){
        cin >> x >> y;
        mapp[x].push_back(y);
        mapp[y].push_back(x);
    }

    cin >> a >> b;
    DFS(a);
    if(visited[b]) cout << "Yes\n";

    else cout << "No\n";
    return 0;
}