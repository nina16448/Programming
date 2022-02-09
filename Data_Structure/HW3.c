#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
typedef struct p{ //存座標用的struct
    int x;
    int y;
} coordinate;

typedef struct l{ //存link的傳送點與接收點
    int t; //傳送點
    int r; //接收點
} link;

typedef struct d{ //存link編號及其傳送點與接收點的距離
    int ID; //編號
    double dl; //傳送點與接收點的距離
    double dll;
} dis;

int nodes_num, links_num, Power, Noise;
//nodes_num是用來存node的數量
//links_num用來存link的數量
//Power用來存P的值
//Noise用來存N的值
coordinate points[100000]; //存每個點的座標
link links[100000]; //存每個link的傳送點與接收點的編號
dis s[100000]; //存每個link編號及其傳送點與接收點的距離
int connect[100000]; //存已連接成功的link
int rec[100000]; //紀錄那些點連過了
int connect_num = 0; //總共有哪些邊連接成功

int cmp(const void *a, const void *b){ //qsort的比較函式 由小到大排
    if((*(dis*)a).dl == (*(dis*)b).dl) return (*(dis*)b).dll - (*(dis*)a).dll;
    return (*(dis*)a).dl - (*(dis*)b).dl;
}

double dl(int Pa, int Pb){ //計算距離的三次方
    int X = points[Pa].x - points[Pb].x;
    int Y = points[Pa].y - points[Pb].y;
    return (X * X + Y * Y) * sqrt(X * X + Y * Y);
}

void greedy(){ //看要連接那些點
    for(int i = 0; i < links_num; i++){ //存每個link的距離
        s[i].ID = i;
        s[i].dl = dl(links[i].t, links[i].r);
        s[i].dll = 0;
        for(int j = 0; j < links_num; j += 39){
            if(i == j) j++;
            s[i].dll += ((points[links[j].t].x - points[links[i].r].x) * (points[links[j].t].x - points[links[i].r].x) + (points[links[j].t].y - points[links[i].r].y) * (points[links[j].t].y - points[links[i].r].y));
        }
    }
    
    qsort(s, links_num, sizeof(dis), cmp); //依照距離大小由小到大排序 距離小的比較不會影響到別的link
    for(int i = 0; i < links_num; i++) printf("%f %f\n", s[i].dl, s[i].dll);

    for(int i = 0; i < links_num; i++){ //放每一條link都放進去看會不會對
        int flag = 0;
        link add = links[s[i].ID]; //現在要放的link

        if(rec[add.t]) continue; //如果link的傳送點已經選過了就跳過這條link
        if(rec[add.r]) continue; //如果link的接收點已經選過了就跳過這條link

        connect[connect_num] = s[i].ID; //把現在這條放進去已連接link裡面
        connect_num++; //選取的數量+1

        rec[add.t] = 1; //讓link的傳送點已經選過了
        rec[add.r] = 1; //讓link的接收點已經選過了

        for(int j = 0; j < connect_num; j++){ //算每一個已連接link的SINR值
            link now = links[connect[j]]; //現在看的這個link
            double SINR = 0;

            for(int k = 0; k < connect_num; k++){ //計算 (power 除以 除了now這條以外其他link的傳送點與now的接收點的距離) 的總和
                if(k == j) continue; //如果是now就跳過

                SINR += Power / dl(links[connect[k]].t, now.r); 
            }
            SINR += Noise; //加上N
            SINR = (Power / dl(now.t, now.r)) / SINR; //(Power 除以 now的距離) 除以 剛剛算的總和加N

            if(SINR - 1 < 1e-6){ //如果有SINR值小於1 就不能選
                flag = 1;
                break;
            }
        }
        
        if(flag){ //不選add這條link
            connect_num--;
            rec[add.t] = 0;
            rec[add.r] = 0;
        }
    }
}

int main(){
    scanf("%d%d%d%d", &nodes_num, &links_num, &Power, &Noise);

    for(int i = 0; i < nodes_num; i++)
        scanf("%*d%d%d", &points[i].x, &points[i].y);
    
    for(int i = 0; i < links_num; i++)
        scanf("%*d%d%d", &links[i].t, &links[i].r);

    greedy();
    
    printf("%d\n", connect_num); //輸出成功連接的數量
    for(int i = 0; i < connect_num; i++)
        printf("%d %d %d\n", connect[i], links[connect[i]].t, links[connect[i]].r);
    
    return 0;
} 