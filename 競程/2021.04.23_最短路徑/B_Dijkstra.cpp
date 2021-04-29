#include <bits/stdc++.h>
using namespace std;
#define point second
#define w first
int n, m, u, v, s, t;
int visited[3000];
int stp[3000];
pair <int, int> rec;
vector < pair <int, int> > mapp[3000];
priority_queue < pair <int, int> , vector < pair <int, int> >, greater < pair <int, int> > > pq;

void greedy(int level){
    visited[level] = 1;
    for(auto x: mapp[level]){
        if(visited[x.point] != 0) continue;

        x.w += stp[level];
        stp[x.point] = min(stp[x.point], x.w);
        x.w = stp[x.point];
        pq.push(x);
    }
    while(!pq.empty() && visited[pq.top().point] != 0)
        pq.pop();

    if(pq.empty()) return;
    
    greedy(pq.top().point);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        cin >> u >> v >> rec.w;
        rec.point = v;
        mapp[u].push_back(rec);
        rec.point = u;
        mapp[v].push_back(rec);
    }
    cin >> s >> t;

    for(int i = 0; i < 3000; i++) stp[i] = 0x3f3f3f;
    stp[s] = 0;
    greedy(s);
    if(visited[t] == 0) cout << "-1\n";
    else 
        cout << stp[t] << "\n";
    return 0;
}