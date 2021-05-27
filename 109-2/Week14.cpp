#include <bits/stdc++.h>
using namespace cv;
using namespace std;
#define ID first
#define x second.first
#define y second.second
typedef long long lint;

lint n, ans, stx, sty, st;
vector <pair <lint, pair <lint, lint> > > U, L;
vector <pair <lint, pair <lint, lint> > > point;
pair <lint, pair <lint, lint> > rec;
lint Cross_Product(lint x1, lint y1, lint x2, lint y2);



bool cmp(pair <lint, pair <lint, lint> > A, pair <lint, pair <lint, lint> > B){
    if(A.x == B.x) return A.y < B.y;
    return A.x < B.x;
}

void Upper_Hull(){
    U.push_back(point[0]);

    U.push_back(point[1]);

    for(lint i = 2; i < n; i++){
        while(U.size() > 1){
            pair <lint, pair <lint, lint> > p, pp;
            lint index = U.size() - 1;
            p = U[index];
            pp = U[index - 1];

            if(Cross_Product(p.x - pp.x, p.y - pp.y, point[i].x - p.x, point[i].y - p.y) >= 0)
                U.pop_back();
            
            else
                break;
            
        }
        U.push_back(point[i]);
    }
}

void Lower_Hull(){
    L.push_back(point[n - 1]);
    L.push_back(point[n - 2]);
    for(lint i = n - 3; i >= 0; i--){
        while(L.size() > 1){
            pair <lint, pair <lint, lint> > p, pp;
            lint index = L.size() - 1;
            p = L[index - 1];
            pp = L[index];
            
            if(Cross_Product(p.x - pp.x, p.y - pp.y, point[i].x - p.x, point[i].y - p.y) <= 0)
                L.pop_back();
            else
                break;
            
        }
        L.push_back(point[i]);
    }
}

lint Cross_Product(lint x1, lint y1, lint x2, lint y2){
    return (x1 * y2) - (x2 * y1);
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);


    img.copyTo(img2);

    cin >> n;
    for(lint i = 1; i <= n; i++){
        rec.ID = i;
        cin >> rec.x >> rec.y;
        point.push_back(rec);
    }

    if(n == 1){
        cout << "1\n1\n";
        return 0;
    }
    sort(point.begin(), point.end(), cmp);
    Upper_Hull();
    Lower_Hull();

    cout << U.size() + L.size() - 1 << "\n";
    for(auto po: U) cout << po.ID << " ";
    for(int i = 1; i < L.size(); i++)
        cout << L[i].ID << " ";


    cout << "\n";
    return 0;
}
