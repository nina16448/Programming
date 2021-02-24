#include <bits/stdc++.h>
using namespace std;
map <string, vector <string> > mp;

int n;
string name, rec, s;

void Make(){
    cin >> name >> rec;

    mp[name].push_back(rec);
    mp[rec].push_back(name);
}

void List(){
    cin >> name;

    for(auto x: mp[name])
        cout << x << " ";
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    while(n--)
        cin >> s;
    
    cin >> n;
    
    while(n--){
        cin >> s;
        if(s == "MakeFriend") Make();

        if(s == "ListFriend") List();
    }

    return 0;
}