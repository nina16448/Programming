#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, k;
int stp[600];
vector <int> graph[600];
queue <int> qu;

void BFS(int level){
    for(auto x: graph[level]){
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
    while(m--){
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    cin >> k;
    while(k--){
        while(!qu.empty()) qu.pop();
        for(int i = 0; i < 600; i++) stp[i] = 0;
        cin >> a >> b;
        qu.push(a);
        stp[a] = 1;
        BFS(a);

        if(stp[b] == 0)
            cout << "-1\n";
        else 
            cout << stp[b] - 1 << "\n";
    }
    return 0;
}
