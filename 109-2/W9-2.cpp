#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
lint n, X, winds, movee;
string s;

bool judge(lint day){
    winds = day / n * movee;
    for(lint i = 0; i < day % n; i++){
        if(s[i] == 'W') winds--;
        if(s[i] == 'E') winds++;
    }
    if(abs(X - winds) <= day) return 1;
    return 0;
}

lint Binary_Search(){
    lint L = 0, R = INT64_MAX, mid;
    while(L < R - 1){
        mid = (L + R) / 2;

        if(judge(mid) == 1) R = mid;
        else L = mid;
    }
    return R;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> s >> X;
    movee = 0;

    for(auto x: s){
        if(x == 'W') movee--;
        if(x == 'E') movee++;
    }

    if(movee + n <= 0) cout << "-1\n";
    else
        cout << Binary_Search() << "\n";
    return 0;
}