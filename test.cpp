#include <bits/stdc++.h>
using namespace std;
int n, a, ans;

void DFS(int level, int Wnum, int Rnum, bool win){ //暴搜一開始傳入值都是0
    //level是指現在在哪一場比賽
    //Wnum是白隊連續贏的次數
    //Rnum是紅隊連續贏的次數
    //win代表現在這場誰贏，1為白隊贏，0為紅隊贏

    if(Wnum == a){ //如果白隊贏a次了，比賽就結束(return)
        ans++; //白隊勝出情況加一
        return;
    }

    if(Rnum == a) return; //紅對連贏a次比賽就結束

    if(win == 0) Wnum = 0; //如果這場是紅隊贏，就把白隊連贏次數歸零
    if(win == 1) Rnum = 0; //如果這場是白隊贏，就把紅隊連贏次數歸零

    if(level == n){ //如果比到第n場
        if(n % 2 && Rnum) return; //如果總共有奇數場，若最後一場是紅隊獲勝，則紅隊贏的總次數會大於白隊，故為紅隊勝利，不能算。
        
        ans++; //平手的情況
        return;
    }

    DFS(level + 1, Wnum + 1, Rnum, 1); //假設下一場為白隊勝利

    DFS(level + 1, Wnum, Rnum + 1, 0); //假設下一場為紅隊勝利

    return;
}

int main(){
    ios::sync_with_stdio(false); //cin加速
    cin.tie(0); //cin加速

    ans = 0; //ans用來記錄幾種情況

    cin >> n >> a;

    DFS(0, 0, 0, 0);

    cout << ans << "\n";
    return 0;
}