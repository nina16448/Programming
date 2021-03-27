#include <bits/stdc++.h>
using namespace std;
int n, L, rec;
vector <int> arr;
int table[2000][2000];

int DP(int L, int R){
    if(L >= R - 1) table[L][R] = 0;

    if(table[L][R] == -1){
        int minnum = 0x3f3f3f3f;
        for(int i = L + 1; i < R; i++){
            int num = DP(L, i) + DP(i, R);
            minnum = min(minnum, num);
        }
        table[L][R] = (arr[R] - arr[L]) + minnum;
    }

    return table[L][R];
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> L;
    arr.push_back(0);
    for(int i = 0; i < n; i++){
        cin >> rec;
        arr.push_back(rec);
    }
    arr.push_back(L);
    for(int i = 0; i < 2000; i++){
        for(int j = 0; j < 2000; j ++){
            if(j > i)
                table[i][j] = -1;
        }
    }
    cout << DP(0, n + 1) << "\n";
    return 0;
}