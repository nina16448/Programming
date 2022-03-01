#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define DEBUG

struct link_info{
    int node1;
    int node2;
    int weight[2];
};
vector <link_info> graph;
int flag;

#ifdef DEBUG
int now;
#endif

void Bellman_Ford(int *weight, int v){
    for(auto links: graph){
        if(weight[links.node1] > weight[links.node2] + links.weight[v]) flag = 0;
        weight[links.node1] = min(weight[links.node1], weight[links.node2] + links.weight[flag]);

        if(weight[links.node2] > weight[links.node1] + links.weight[v]) flag = 0;
        weight[links.node2] = min(weight[links.node2], weight[links.node1] + links.weight[flag]);
    }
    #ifdef DEBUG
    cout << now << " : ";
    for(int i = 0; i < 5; i++) cout << weight[i] << " ";
    cout << "\n";
    #endif
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int nodes_num, dsts_num, links_num, ID;
    vector <int> dsts;
    link_info link;

    cin >> nodes_num >> dsts_num >> links_num;

    int weight[dsts_num][nodes_num];
    for(int i = 0; i < dsts_num; i++){
        for(int j = 0; j < nodes_num; j++){
            weight[i][j] = 0x3f3f3f3f;
        }
    }

    for(int i = 0; i < dsts_num; i++){
        cin >> ID;
        dsts.push_back(ID);
    }

    for(int i = 0; i < links_num; i++){
        cin >> ID >> link.node1 >> link.node2 >> link.weight[0] >> link.weight[1];
        graph.push_back(link);
    }

    for(int i = 0; i < (int)dsts.size(); i++){
        flag = 0;
        weight[i][dsts[i]] = 0;
        while(!flag){
            flag = 1;
            #ifdef DEBUG
            now = dsts[i];
            #endif
            Bellman_Ford(weight[i], 0);
        }
    }
    
    for(int i = 0; i < nodes_num; i++){
        cout << i << "\n";
        for(int j = 0; j < (int)dsts.size(); j++){
            if(i == dsts[j]) continue;
            cout << dsts[j] << " " << weight[j][i] << "\n";
        }
    }
    return 0;
}
