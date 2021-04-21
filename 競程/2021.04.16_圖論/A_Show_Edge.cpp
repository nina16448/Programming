#include <bits/stdc++.h>
using namespace std;
#define a first
#define b second

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    pair <int, int> arr[100000];
    int n, m, u, k, r;
    cin >> n >> m;
    for(int i = 0; i < n; i++)
        cin >> u >> arr[u].a >> arr[u].b;
    
    cin >> k;
    while(k--){
        cin >> r;
        cout << arr[r].a << " " << arr[r].b << "\n";
    }
    return 0;
}