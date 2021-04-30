#include <bits/stdc++.h>
using namespace std;
int n, m, a, b;
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
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    Union_Find UF;
    UF.init();
    for(int i = 0; i < m; i++){
        cin >> a >> b;  
        UF.Union(a, b);
    }
    cin >> a >> b;
    if(UF.root[a] == UF.root[b]) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}