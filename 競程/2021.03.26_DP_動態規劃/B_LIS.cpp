#include <bits/stdc++.h>
using namespace std;
int n, rec, num = 0;
vector <int> arr;
int DP[10010];

int Binary_search(int k){
    int R = arr.size(), L = -1, mid;
    while(L < R - 1){
        mid = (L + R) / 2;
        if(arr[mid] >= k) R = mid;
        else L = mid;
    }
    return R;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    arr.push_back(0X3f3f3f3f);
    while(n--){
        cin >> rec;
        int index = Binary_search(rec);
        if(arr.size() == index) arr.push_back(rec);
        else arr[index] = min(arr[index], rec);
    }
    cout << arr.size() << "\n";
    return 0;
}