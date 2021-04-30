#include <bits/stdc++.h>
using namespace std;
#define w first
#define a second.first
#define b second.second
int n, m, sum;

pair < int, pair <int, int> > rec;
priority_queue < pair < int, pair <int, int> > , vector < pair < int, pair <int, int> > >, greater < pair < int, pair <int, int> > > > pq;

struct Union_Find{
    int root[100010];
    int tree[100010];
    void init(){
        for(int i = 0; i < 100010; i++){
            root[i] = i;
            tree[i] = 1;
        }
    }
    int Find(int x){
        if(x == root[x]) return x;
        return root[x] = Find(root[x]);
    }
    void Union(int x, int y){
        x = Find(x);
        y = Find(y);

        if(x == y) return;

        if(tree[x] > tree[y]){
            root[y] = x;
            tree[x] += tree[y];
        }
        else{
            root[x] = y;
            tree[y] += tree[x];
        }
        sum += pq.top().w;
    }
};



int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    Union_Find UF;
    UF.init();

    for(int i = 0; i < m; i++){
        cin >> rec.a >> rec.b >> rec.w;
        pq.push(rec);
    }

    while(!pq.empty()){
        UF.Union(pq.top().a, pq.top().b);
        pq.pop();
    }
    int flag = UF.Find(0);
    for(int i = 1; i < n; i++){
        if(UF.Find(i) != flag){
            flag = -1;
            break;
        }
    }
    if(flag == -1) cout << "-1\n";
    else
        cout << sum << "\n";
    return 0;
}