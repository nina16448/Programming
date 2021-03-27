#include <bits/stdc++.h>
using namespace std;
#define w first
#define v second
int n, m, num;
set <int> stp;
vector <pair <int, int> > arr;
pair <int, int> rec;
int table[101000][1010];

int DP(int i, int j){
    if(i == 0 || j == 0) return 0;
    if(table[i][j] == -1){
        if(arr[j].w > i)
            table[i][j] = DP(i, j - 1);
        else{
            int a = DP(i, j - 1);
            int b = arr[j].v + DP(i - arr[j].w, j - 1);
            table[i][j] = max(a, b);
        }
    }
    
    return table[i][j];
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    arr.push_back(rec);
    for(int i = 0; i < n; i++){
        cin >> rec.w >> rec.v;
        arr.push_back(rec);
    }

    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            table[i][j] = -1;

    cout << DP(m, n) << "\n";
    
    return 0;
}