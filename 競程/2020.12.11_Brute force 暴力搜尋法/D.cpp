#include <bits/stdc++.h>
using namespace std;

vector <int> v;
int n;
bool used[9];

void DFS(int level){
    if(level==n){
        for(auto x:v)
            cout<<x<<" ";
        cout<<"\n";
    }
    for(int i=1;i<=n;i++){
        if(used[i]) continue;
        
        used[i]=1;
        v.push_back(i);
        DFS(level+1);

        used[i]=0;
        v.pop_back();
    }
}

int main(){
    cin>>n;
    DFS(0);
    return 0;
}