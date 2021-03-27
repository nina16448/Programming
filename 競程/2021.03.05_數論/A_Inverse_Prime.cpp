#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

lint fp(lint a, lint p, lint m){
    lint result=1;
    while(p != 0){
        if(p % 2 == 1){
            result *= a;
            result %= m;
        }
        a *= a;
        a %= m;
        p = p / 2;
    }
    return result;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    lint a, b, m;
    cin >> a >> m;
    
    cout << fp(a, m - 2, m) << "\n";
    return 0;
}