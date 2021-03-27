#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
priority_queue <lint, vector <lint>, greater <lint> > pq;
queue <lint> qu;
lint t, n, m, rec, sum, maxx;

void greedy(){
    while(!qu.empty()){
        lint top = pq.top();
        pq.pop();
        top += qu.front();
        pq.push(top);
        qu.pop();
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--){
        while(!pq.empty())
            pq.pop();
        while(!qu.empty())
            qu.pop();
        sum = 0;

        cin >> n >> m;
        for(lint i = 0; i < n; i++){
            cin >> rec;
            qu.push(rec);
        }
        for(lint i = 0; i < m; i++)
            pq.push(0);

        greedy();
        
        lint size = pq.size();
        for(lint i = 0; i < size - 1; i++)
            pq.pop();
        
        cout << pq.top() << "\n";
    }
    return 0;
}