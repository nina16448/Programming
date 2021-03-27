#include <bits/stdc++.h>
using namespace std;
int n, rec, num = 0;
vector <int> arr;
int DP[10010];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    arr.push_back(0X3f3f3f3f);
    while(n--){
        cin >> rec;
        for(int j = arr.size() - 1; j >= 0; j--){
            if(arr[j] < rec){
                if(arr.size() == j + 1) arr.push_back(rec);
                else arr[j + 1] = min(arr[j + 1], rec);
            }
            if(j == 0 && arr[j] > rec) arr[j] = min(arr[j], rec);
        }    
    }
    cout << arr.size() << "\n";
    return 0;
}