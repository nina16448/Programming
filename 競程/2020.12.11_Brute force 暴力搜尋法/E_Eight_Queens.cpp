#include <bits/stdc++.h>
using namespace std;

string mapp[8];
long long int num;
int clm[8], dia1[20], dia2[20];

void DFS(int row){
    if(row == 8){
        num++;
        return;
    }
    
    for(int i = 0; i < 8; i++){
        if(mapp[row][i] == '*' || clm[i] || dia1[row+i] || dia2[row - i + 7])
            continue;

        clm[i] = 1;
        dia1[row + i] = 1;
        dia2[row - i + 7] = 1;
        DFS(row + 1);

        clm[i] = 0;
        dia1[row+i] = 0;
        dia2[row-i+7] = 0;
    }
}

int main(){
    for(int i = 0; i < 8; i++)
        cin >> mapp[i];
    
    DFS(0);
    cout << num << "\n";
    return 0;
}
