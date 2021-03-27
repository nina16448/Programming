#include <bits/stdc++.h>
using namespace std;
string s, t;
int table[2000][2000];

int DP(int x, int y){
    if(x == 0 || y == 0) table[x][y] = 0;

    if(table[x][y] == -1){
        if(s[x - 1] == t[y - 1])
            table[x][y] = DP(x - 1, y - 1) + 1;
        else
            table[x][y] = max(DP(x - 1, y), DP(x, y - 1));
    }

    return table[x][y];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> s >> t;
    for(int i = 0; i < 2000; i++)
        for(int j = 0; j < 2000; j ++)
            table[i][j] = -1;
    
    

    cout << DP(s.size(), t.size()) << "\n";

    return 0;
}