#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
lint ExGCD(lint a, lint b, lint &x, lint &y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    lint d = ExGCD(b, a % b, x, y);
    lint tmp = x;
    x = y;
    y = tmp - (a / b * y);
    return d;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    lint a, b, m, x, y;
    cin >> a >> m;

    ExGCD(a, m, x, y);

    if(x < 0) x += m;
    
    cout << x << "\n";
    return 0;
}