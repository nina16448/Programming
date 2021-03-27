#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
lint N, rec, times;
vector <lint> arr;

void greedy(){
    times = 0;
    sort(arr.begin(), arr.end());

    while(arr.size() > 3){
        lint len = arr.size();
        lint stp1 = arr[0] + arr[0] + arr.back() + arr[len - 2];
        lint stp2 = arr[0] + arr[1] + arr[1] + arr.back();

        times += min(stp1, stp2);
        arr.pop_back();
        arr.pop_back();
    }
    if(arr.size() == 1) times += arr[0];

    if(arr.size() == 2) times += max(arr[0], arr[1]);
    
    if(arr.size() == 3) for(auto x: arr) times += x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    for(lint i = 0; i < N; i++){
        cin >> rec;
        arr.push_back(rec);
    }
    greedy();

    cout << times << "\n";
    return 0;
}