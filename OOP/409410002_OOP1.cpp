#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define before 0
#define after 1

class link_info{ //關於link資訊的class
public:
    int node1;
    int node2;
    int weight[2]; //邊的權重，0是舊的，1是新的
};
vector <link_info> graph; //用vector建圖
int flag;
int weight[10000]; //Bellman ford用來存原點到每個點的最短距離
map <pair <int, int>, int[2]> road; //用map存每個node到終點的最短路徑的下一個點。key是點i跟各個終點的ID。value有兩項，第0項是存舊的圖的下一步，第1項是存新的圖的下一步

void Bellman_Ford(int v, int dstID){ //判斷每一個link會不會更新最短路徑
    for(auto links: graph){ //圖上的每一個link
        if(weight[links.node1] > weight[links.node2] + links.weight[v] || (weight[links.node1] == weight[links.node2] + links.weight[v] && road[{links.node1, dstID}][v] > links.node2)){
            //先判斷node2走到node1的情況。如果走這條link會使目前node1到起點的最短距離更短，或走這條link會跟目前node1到起點的最短距離一樣，但node2編號比較小就會跑進來
            road[{links.node1, dstID}][v] = links.node2; //將node1要走的下一個點設為node2
            flag = 0; //有變更，因此將flag設為0
            weight[links.node1] = weight[links.node2] + links.weight[v]; //更新node1到起點的最短距離
        }

        if(weight[links.node2] > weight[links.node1] + links.weight[v] || (weight[links.node2] == weight[links.node1] + links.weight[v] && road[{links.node2, dstID}][v] > links.node1)){ 
            //因為是雙向邊，所以也要判斷從node1走到node2的情況，基本上就是上面的兩個點換位置
            road[{links.node2, dstID}][v] = links.node1;
            flag = 0;
            weight[links.node2] = weight[links.node1] + links.weight[v];
        }
    }
}

int main(){
    int nodes_num, dsts_num, links_num, ID; 
    vector <int> dsts; //存各個終點的ID
    link_info link; //link的資訊

    cin >> nodes_num >> dsts_num >> links_num;
    
    for(int i = 0; i < dsts_num; i++){ //輸入各個終點
        cin >> ID;
        dsts.push_back(ID);
    }

    for(int i = 0; i < links_num; i++){ //輸入每條link的資訊
        cin >> ID >> link.node1 >> link.node2 >> link.weight[before] >> link.weight[after];
        graph.push_back(link); //把每一條link都塞進vector裡面
    }

    for(int i = 0; i < dsts_num; i++){ //i代表第幾個終點，把每個終點當成起點走到其他點
        for(int ver = 0; ver < 2; ver++){ //跑舊的圖跟新的圖，0是舊的，1是新的
            for(int j = 0; j < nodes_num; j++) //初始化，將起點到每個點的距離設為無限大
                weight[j] = 0x3f3f3f3f;
            flag = 0; //用來判斷Bellman ford有沒有繼續更新，沒有則跳出while迴圈
            weight[dsts[i]] = 0; //起點到起點距離為0

            while(!flag){ //如果flag == 0，則代表Bellman ford還有在繼續更新
                flag = 1;
                Bellman_Ford(ver, dsts[i]);
            }
        }
    }
    
    for(int i = 0; i < nodes_num; i++){ //印出舊路線
        cout << i << "\n";
        for(auto dst: dsts){
            if(i == dst) continue; //如果現在看的點i是終點，就繼續看下一個終點
            cout << dst << " " << road[{i, dst}][before] << "\n"; //印出終點的ID，以及點i到終點的最短路徑的下一步node的ID
        }
    }

    for(int i = 0; i < nodes_num; i++){ //印出新路線
        flag = 0;
        for(auto dst: dsts){
            if(road[{i, dst}][before] == road[{i, dst}][after]) continue; //如果路線未更新，就不用印出來
            if(flag == 0) cout << i << "\n"; //如果有更新的路徑，就印出的這個點的ID，跟更新的路

            cout << dst << " " << road[{i, dst}][after] << "\n"; 
            flag = 1; //已經印過是哪個點了，所以將flag設為1
        }
    }

    return 0;
}
