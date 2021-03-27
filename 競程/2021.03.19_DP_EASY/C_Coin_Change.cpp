#include <bits/stdc++.h>
using namespace std;
int n, m, rec;
int coin[1000001];

int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++) coin[i] = 0x3f3f3f3f;
    while(n--){
        cin >> rec;

        for(int i = 1; i <= m; i++){
            if(i >= rec){
                coin[i] = min(coin[i], 1 + coin[i - rec]);
            }
        }
    }
    if(coin[m] == 0x3f3f3f3f) cout << "-1\n";
    else cout << coin[m] << "\n";
    return 0;
}