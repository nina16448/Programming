#include <bits/stdc++.h>
using namespace std;

int n;
struct point{
    double x;
    double y;
};

double dis(int a, int b, struct point p[]){
    double X,Y;
    X= p[a].x - p[b].x;
    Y= p[a].y - p[b].y;
    return sqrt((X*X)+(Y*Y));
}

int main(){
    double min=9999999;
    scanf("%d",&n);
    //cin >> n;
    struct point p[n];
    for(int i=0;i<n;i++){
        //cin >> p[i].x >> p[i].y;
        scanf("%lf %lf", &p[i].x, &p[i].y);
    }
    min=dis(0,1,p);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) continue;
            double rec=dis(i,j,p);
            if(rec<min) min=rec;
        }
    }
    printf("%.7f",min);
    //cout << min << "\n";
    return 0;
}