#include <bits/stdc++.h>
using namespace std;
int n, rec, ans;
vector <int> power1;
priority_queue <int, vector<int>, greater<int> > power2;

void greedy(){
    sort(power1.begin(), power1.end());

    while(!power2.empty()){
        for(int i = 0; i < n; i++){
            if(power1[i] > power2.top()){
                power1[i] = 0;
                ans++;
                break;
            }
        }
        power2.pop();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    while(cin >> n && n != 0){
        power1.clear();
        ans = 0;
        while(!power2.empty())
            power2.pop();

        for(int i = 0; i < n; i++){
            cin >> rec;
            power2.push(rec);
        }
        for(int i = 0; i < n; i++){
            cin >> rec;
            power1.push_back(rec);
        }
        greedy();

        cout << ans << "\n";
    }
    return 0;
}