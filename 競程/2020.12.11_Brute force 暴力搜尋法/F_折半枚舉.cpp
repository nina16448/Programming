#include <bits/stdc++.h>
using namespace std;

int n;
int arr[50];
vector <int> sumarr[2];

bool cmp(int a, int b){
    return a < b;
}

void DFS(int level, int sum, int end, int times){
    if(sum > 1000) return;

    if(level == end){
        sumarr[times].push_back(sum);
        return;
    }

    DFS(level+1, sum+arr[level], end, times);

    DFS(level+1, sum, end, times);
}

int main(){
    ios::sync_with_stdio(false);
    cin >> n;    
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }

    DFS(0, 0, n/2, 0);
    DFS(n/2, 0, n, 1);
    
    sort(sumarr[0].begin(), sumarr[0].end(), cmp);
    
    long long int sum = 0;
    
    for(auto x: sumarr[1]){
        auto itr = upper_bound(sumarr[0].begin(), sumarr[0].end(), 1000-x);
        long long int num = 0;
        num = itr - sumarr[0].begin();
        sum += num;
    }
    cout << sum;
    return 0;
}
