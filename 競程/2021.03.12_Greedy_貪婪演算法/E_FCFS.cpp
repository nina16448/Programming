#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
lint t, n, m, rec;
priority_queue <lint, vector <lint>, greater <lint> > pq;
queue <lint> qu;
vector <lint> arr;

lint greedy(lint num){
    while(!pq.empty())
        pq.pop();
    while(!qu.empty())
        qu.pop();

    for(auto x: arr)
            qu.push(x);
    for(lint i = 0; i < num; i++)
        pq.push(0);
    
    while(!qu.empty()){
        lint top = pq.top();
        pq.pop();
        top += qu.front();
        pq.push(top);
        qu.pop();
    } 
    lint size = pq.size();
    for(lint i = 0; i < size - 1; i++)
        pq.pop();

    return pq.top();
}

lint Binary_search(){
    lint r = n + 1, l = 0, mid;
    while(l != r - 1){
        mid = (l + r) / 2;

        if(greedy(mid) <= m) r = mid;
        else l = mid;
    }
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--){
        arr.clear();
        cin >> n >> m;
        for(int i = 0; i < n; i++){
            cin >> rec;
            arr.push_back(rec);
        }
        if(Binary_search() > n) cout << "-1\n";
        else
            cout << Binary_search() << "\n";

    }
    return 0;
}