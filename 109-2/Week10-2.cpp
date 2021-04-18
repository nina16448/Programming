#include <bits/stdc++.h>
using namespace std;
int n, sum,rec;
vector <int> arr;
vector <int> ans;

int Binary_search(int index){
    int L = -1, R = index + 1, mid;

    while(L != R - 1){
        mid = (R + L) / 2;

        if(mid == 0) L = mid;
        else if(arr[index] - arr[mid - 1] < sum) R = mid;
        else L = mid;
    }

    return L;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> sum;
    arr.push_back(0);
    for(int i = 1; i <= n; i++){
        cin >> rec;
        arr.push_back(rec + arr[i - 1]);
    }
    
    for(int i = 1; i <= n; i++){
        int index = Binary_search(i);

        if(index - 1 < 0 ||arr[i] - arr[index - 1] < sum) ans.push_back(-1);
        else 
        ans.push_back(index);
    }

    for(auto x: ans) cout << x << " ";
    cout << "\n";
    
    return 0;
}
