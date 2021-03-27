#include <bits/stdc++.h>
using namespace std;
int n, rec;
vector <int> DP;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    while(n--){
        cin >> rec;

        int index = lower_bound(DP.begin(), DP.end(), rec) - DP.begin();
        if(index == DP.size()) DP.push_back(rec);
        else DP[index] = min(DP[index], rec);
    }
    cout << DP.size() << "\n";
    return 0;
}