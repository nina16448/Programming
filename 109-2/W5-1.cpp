#include <bits/stdc++.h>
using namespace std;

struct table{
    string name;
    int age;
    int weight;
};

bool cmp(table A, table B){
    if(A.name == B.name){
        if(A.age == B.age)
            return A.weight > B.weight;
        return A.age > B.age;
    }
    return A.name < B.name;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, reca, recw;
    string s;
    struct table data;
    vector <struct table> arr;
    cin >> n;
    while(n--){
        cin >> data.name >> data.age >> data.weight;
        arr.push_back(data);
    }
    sort(arr.begin(), arr.end(), cmp);

    for(auto x: arr)
        cout << x.name << " " << x.age << " " << x.weight << "\n";
    return 0;
}