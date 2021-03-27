#include <bits/stdc++.h>
using namespace std;
#define v first
#define w second
pair <int, int> rec;
int table[2000][2];
int n, m;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    int flag = 0;
    for(int i = 0; i < n; i++){
        cin >> rec.v >> rec.w;
        for(int i = 1; i <= m; i++){
            if(i < rec.w) table[i][flag] = table[i][!flag];
            else table[i][flag] = max(table[i][!flag], rec.v + table[i - rec.w][!flag]);
        }
        flag = !flag;
    }
    cout << table[m][!flag] << "\n";
    return 0;
}