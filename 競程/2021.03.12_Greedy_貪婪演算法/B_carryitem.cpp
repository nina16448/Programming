#include <bits/stdc++.h>
using namespace std;
int t, n, m, rec, money, package;
priority_queue <int, vector<int>, greater<int> > pack;
vector <int> stu;

void greedy(){
    sort(stu.begin(), stu.end());
    while(!pack.empty()){
        for(int i = 0; i < m; i++){
            if(stu[i] >= pack.top()){
                money += stu[i];
                package++;
                stu[i] = 0;
                break;
            }
        }
        pack.pop();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--){
        stu.clear();
        while(!pack.empty())
            pack.pop();
        money = 0;
        package = 0;

        cin >> n >> m;

        for(int i = 0; i < n; i++){
            cin >> rec;
            pack.push(rec);
        }
        for(int i = 0; i < m; i++){
            cin >> rec;
            stu.push_back(rec);
        }


        greedy();

        if(package == n)
            cout << money << "\n";
        else
            cout << "-1\n";
    }
    
    return 0;
}