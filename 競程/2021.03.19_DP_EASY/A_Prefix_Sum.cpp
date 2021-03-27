#include <bits/stdc++.h>
using namespace std;
int arr[20000];
int n, m, rec, l, r;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    for(int i = 1; i <= n; i++){
        cin >> rec;
        arr[i] = arr[i - 1] + rec;
    }

    while(m--){
        cin >> l >> r;
        cout << arr[r] - arr[l - 1] << "\n";
    }
    
    return 0;
}