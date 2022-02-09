#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

typedef struct array{ //linked list
    int ID;
    struct array* next;
}arr;

typedef struct nd{ //用來建圖及建樹的資料型態
    int value; //儲存點的權重
    arr* link; //儲存與其相鄰的邊
    int dis; //紀錄點到0號節點的最小cost
    int parent; //父節點
    arr* child; //儲存其所有子節點
}node;

node graph[10000];
int total_cost, num_nodes, num_link, packet_size; 
//total_cost用來計算總共的cost
//num_nodes是總共有幾個點
//num_link是總共有幾條邊
//packet_size是packet的大小

arr* push_back(arr* link, int nodeID){ //把放資料進去linked list
    arr* rec = (arr*) malloc(sizeof(arr));
    rec->ID = nodeID;
    rec->next = link;
    return rec;
}

int DFS(int level){ //用遞迴算總共的cost
    arr* rec = graph[level].child;
    int value_sum = 0;

    while(rec != NULL){
        value_sum += DFS(rec->ID);
        rec = rec->next;
    }

    value_sum += graph[level].value;
    if(level != 0){
        total_cost += value_sum / packet_size;
        if(value_sum % packet_size) total_cost++;
    }

    return value_sum;
}

int cnt_cost(int level, int value, int cost){ //計算如果i點的父節點為level時的cost
    if(level == 0) return cost;

    value += graph[level].value;
    cost += value / packet_size;
    if(value % packet_size) cost++;

    if(level == graph[level].parent) return 0x3f3f3f3f;

    return cnt_cost(graph[level].parent, value, cost);
}

int greedy(){ //用greedy建樹
    int flag = 0;

    for(int i = 1; i < num_nodes; i++){ //從1開始，因為0不會有父節點
        arr* rec = graph[i].link; //儲存與第i個點相鄰的點
        int dis; //dis存 當rec為第i點的父節點時，到第0點的cost

        while(rec != NULL){
            if(rec->ID != graph[i].parent){
                dis = cnt_cost(rec->ID, graph[i].value, 0);
                if(graph[i].dis > dis){
                    graph[i].dis = dis;
                    graph[i].parent = rec->ID;
                    flag = 1;
                }
            }
            rec = rec->next;
        }
    }
    return flag;
}

int main(){
    int ID, weight, node1, node2;
    total_cost = 0;
    scanf("%d%d%d", &num_nodes, &num_link, &packet_size); //輸入點數量、邊數量及packet大小
    
    for(int i = 0; i < num_nodes; i++){ 
        scanf("%d%d", &ID, &weight); //輸入每一點的權重
        graph[ID] = (node){weight, NULL, 0x3f3f3f3f, i, NULL}; //初始化每一點
    }

    for(int i = 0; i < num_link; i++){ //建圖，建雙向邊的圖
        scanf("%d%d%d", &ID, &node1, &node2);
        graph[node1].link = push_back(graph[node1].link, node2);
        graph[node2].link = push_back(graph[node2].link, node1);
    }

    graph[0].dis = 0; //0號節點到0號節點的cost為0

    for(int i = 0; i < num_nodes; i++){ //要更新n-1次dis
        if(greedy() == 0) break; //全跑會TLE所以如果沒更新了就break
    }

    for(int i = 1; i < num_nodes; i++) //建每個點的子節點
        graph[graph[i].parent].child = push_back(graph[graph[i].parent].child, i);
    
    DFS(0);

    printf("%d %d\n", num_nodes, total_cost);
    for(int i = 0; i < num_nodes; i++) printf("%d %d\n", i, graph[i].parent);
    return 0;
}