#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, maxsum = -20000, maxx, maxy, x = 1, y = 1, sum = 0, rec;
    cin >> n;
    for(int i = 1; i <= n; i++){
        y = i;
        cin >> rec;
        sum += rec;

        if(sum > maxsum){
            maxsum = sum;
            maxx = x;
            maxy = y;
        }

        if(sum < 0){
            x = i + 1;
            sum = 0;
        }
    }
    cout << maxx << " " << maxy << "\n" << maxsum << "\n";
    return 0;
}