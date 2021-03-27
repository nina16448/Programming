#include <bits/stdc++.h>
using namespace std;
int n,x;
long long int maxx=0;
struct arr{
    long long int v;
    long long int w;
};

void DFS(int level,long long int w,long long int rec,struct arr A[]){
    if(w > x) return;
    if(level==n){
        if(rec>=maxx) maxx=rec;
        return;
    }
    DFS(level+1, w+A[level].w, rec+A[level].v, A);

    DFS(level+1, w, rec, A);
}

int main(){
    struct arr A[21];
    scanf("%d %d",&n,&x);
    for(int i=0; i<n; i++){
        scanf("%lld %lld",&A[i].v ,&A[i].w);
    }
    DFS(0, 0, 0, A);

    printf("%lld",maxx);

    return 0;
}