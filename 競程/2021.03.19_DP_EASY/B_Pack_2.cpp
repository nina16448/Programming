#include <bits/stdc++.h>
using namespace std;
#define w first
#define v second
int n, m;
pair <int, int> rec;
int DP[100100][2];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int flag = 0; 
    while(n--){
        cin >> rec.w >> rec.v;

        for(int i = 1; i <= m; i++){
            if(rec.w > i) DP[i][flag] = DP[i][!flag];
            else DP[i][flag] = max(DP[i][!flag], rec.v + DP[i - rec.w][!flag]);
        }
        flag = !flag;
    }
    
    cout << DP[m][!flag] << "\n";
    return 0;
}