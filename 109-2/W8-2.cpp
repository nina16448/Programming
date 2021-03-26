#include <bits/stdc++.h>
using namespace std;
int n, m, rec;
vector <int> arr;
int coin[1000001];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> rec;
        arr.push_back(rec);
    }
    cin >> m;
    for(int i = 1; i <= m; i++) coin[i] = 0x3f3f3f3f;

    for(auto x: arr){
        for(int i = 1; i <= m; i++){
            if(i >= x)
                coin[i] = min(coin[i], 1 + coin[i - x]);
        }
    }
    if(coin[m] == 0x3f3f3f3f) cout << "-1\n";
    else cout << coin[m] << "\n";
    return 0;
}