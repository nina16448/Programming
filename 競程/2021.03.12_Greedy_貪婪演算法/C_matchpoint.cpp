#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

int main(){
    lint t, rec;
    double ans;
    string s;
    vector <lint> x, y;
    stringstream ss;

    getline(cin, s);
    ss << s;
    ss >> t;

    while(t--){
        ans = 0;
        x.clear();
        y.clear();
        ss.clear();
        getline(cin, s);

        ss << s;
        while(ss >> rec)
            x.push_back(abs(rec));
        
        ss.clear();

        getline(cin, s);
        ss << s;
        while(ss >> rec)
            y.push_back(abs(rec));
        
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        reverse(y.begin(), y.end());

        for(int i = 0; i < (int)x.size(); i++)
            ans += sqrt(x[i] * x[i] + y[i] * y[i]);
        
        cout << (lint)ans << "\n";
    }
    
    return 0;
}