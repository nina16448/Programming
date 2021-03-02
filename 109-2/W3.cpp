#include <bits/stdc++.h>
using namespace std;
vector <vector <int> > arr;
vector <int> rec;
int n, m, num, ans;

void solve(){ 
    int top = 0;
    for(int i = 0; i < n; i++){
        for(int j = top; j < m; j++){
            if(arr[j][i] == 1){
                swap(arr[j], arr[top]);
                top++;
                for(int k = top; k < m; k++){
                    if(arr[k][i] == 1){
                        for(int l = 0; l < n; l++){
                            arr[k][l] = (arr[k][l] + arr[top - 1][l]) % 2;
                        }
                    }
                }
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    ans = 0;
    for(int i = 0; i < m; i++){
        rec.clear();
        for(int j = 0; j < n; j++){
            cin >> num;
            rec.push_back(num);
        }
        arr.push_back(rec);
    }
    rec.clear();
    for(int i = 0; i < n; i++)
        rec.push_back(0);

    solve();
    
    for(int i = 0; i < m; i++)
        if(arr[i] != rec) ans++; 

    /*
    cout << "\n";
    for(auto x: arr){
        for(auto y: x)
            cout << y << " ";
        cout << "\n";
    }*/

    cout << ans << "\n";
    return 0;
}