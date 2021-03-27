#include <bits/stdc++.h>
using namespace std;
int arr[10000];
int n;
int ans;
void DFS(int level,int sum){
    if(sum>1000) return;
    if(level==n){
        ans++;
        return;
    }
    DFS(level+1,sum+arr[level]);
    DFS(level+1,sum);
}

int main(){
    
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    DFS(0,0);
    cout<<ans<<"\n";
    return 0;
}
