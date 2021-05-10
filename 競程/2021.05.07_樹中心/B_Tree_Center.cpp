#include <bits/stdc++.h>
using namespace std;
int n, a, b, maxx, p, q;
queue <int> qu;
int stp[200010], root[200010];
vector <int> table[200010];

void BFS(int level){
    for(auto x: table[level]){
        if(stp[x] != 0) continue;

        qu.push(x);
        stp[x] = stp[level] + 1;
        root[x] = level;
    }
    qu.pop();
    if(qu.empty()) return;
    BFS(qu.front());
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n - 1; i++){
        cin >> a >> b;
        table[a].push_back(b);
        table[b].push_back(a);
    }
    while(!qu.empty()) qu.pop();
    stp[1] = 1;
    qu.push(1);
    BFS(1);
    maxx = -1;

    for(int i = 0; i <= n; i++){
        if(stp[i] > maxx){
            p = i;
            maxx = stp[i];
        }
        stp[i] = 0;
    }
    while(!qu.empty()) qu.pop();

    qu.push(p);
    stp[p] = 1;
    root[p] = p;
    BFS(p);
    maxx = -1;

    for(int i = 1; i <= n; i++){
        if(stp[i] > maxx){
            p = i;
            maxx = stp[i];
        }
    }
    int r = (maxx - 1) ;
    int ans = p, anss = p;
    if(r % 2){
        for(int i = 0; i < r / 2; i++)
            ans = root[ans];
        for(int i = 0; i < r / 2 + 1; i++)
            anss = root[anss];
        cout << min(ans, anss) << "\n";
    }
    else{
        for(int i = 0; i < r / 2; i++)
            ans = root[ans];
    
        cout << ans << "\n";
    }
    

    return 0;
}