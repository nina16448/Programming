#include <bits/stdc++.h>
using namespace std;
int n, m, rec;
int stp[1000001][30];
int coin[1000001];

int main(){
    cin >> n >> m;
    int record = n;
    for(int i = 1; i <= m; i++) coin[i] = 0x3f3f3f3f;
    for(int j = 0; j < n; j++){
        cin >> rec;

        for(int i = 1; i <= m; i++){
            if(i >= rec){
                int tack = 1 + coin[i - rec];
                if(tack < coin[i]){
                    for(int k = 0; k < n; k++) stp[i][k] = 0;
                    stp[i][j]++;
                    for(int k = 0; k < n; k++)
                        stp[i][k] += stp[i - rec][k];
                }
                coin[i] = min(coin[i], tack);
            }
        }
    }
    if(coin[m] == 0x3f3f3f3f) cout << "-1\n";
    else{
        cout << coin[m] << "\n";
        for(int i = 0; i < n; i++)
            cout << stp[m][i] << " ";
        
        cout << "\n";
    }
    return 0;
}