#include <bits/stdc++.h>
using namespace std;
int n, m, a, b, k, s, d;
int stp[2000];
vector <int> mapp[1050];
queue <int> qu;

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
    for(int i = 0; i < n; i++){
        cin >> a >> b;
        mapp[a].push_back(b);
        mapp[b].push_back(a);
    }
    cin >> k;

    while(k--){
        while(!qu.empty()) qu.pop();
        for(int i = 0; i < 2000; i++) stp[i] = 0;
        cin >> s >> d;
        qu.push(s);
        stp[s] = 1;
        BFS(s);
        cout << stp[d] - 1 << "\n";
    }
    
    return 0;
}