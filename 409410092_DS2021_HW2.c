//This program is to try to get the lowest cost of tranferring data to root.
//On each node, program will calculus the total cost of each path to root.
//And choose the lowest cost as the path to root.
//Considering the cost might change after any of the node's decision,
//program will do n(node's count) times continuing updating the cost.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//data type of linked list for hash table
struct lnode{
  int value;
  struct lnode *next;
};

//data type for information of node
struct nnode{
  int ini_weight;
  int weight;     //weight with subtree
  int parent;
  int cost;
  int level;
  struct lnode *link; //linked node list
};

//nodeCnt is for total number of node, linkCnt is for total number of link
//packSize is for package Size, maxLevel is for the maxlevel of aggregation tree
//nodeLevel is for each level has which node, node is for tree node
int nodeCnt, linkCnt, packSize, maxLevel;
struct lnode *nodeLevel[10000];
struct nnode node[10000];

//insert a new data to the front of the assigned list
struct lnode *insert(struct lnode *list, int value){
  struct lnode *new_node=(struct lnode *) malloc(sizeof(struct lnode));
  new_node->value=value;
  new_node->next=list;
  return new_node;
}

//swap two integer
void swap(int *value1, int *value2){
  int tmp=*value1;
  *value1=*value2;
  *value2=tmp;
}

//calculus the total cost from the assigned level to root 
int cal_cost(int level, int w){
  int tmp_cost=0;
  int visited[10000]={0};

  //calculus
  while(level!=0 && visited[level]!=1){
    visited[level]=1;
    tmp_cost=tmp_cost+((node[level].weight+w)/packSize)+1;
    if ((node[level].weight+w)%packSize==0) tmp_cost-=1;
    level=node[level].parent;
  }
  
  //root is not 0
  if (level!=0) return 0x3f3f3f3f;
  return tmp_cost;
}

//node changes the path, plus or minus the node's weight on the path
//mode 0 representing minus, 1 representing plus
void change(int level, int w, int mode){
  if (mode==0) w=-w;

  //not choosing path yet
  if (level==node[level].parent) return;

  //changing
  level=node[level].parent;
  while(level!=0){
    node[level].weight+=w;
    level=node[level].parent;
  }
}

//traverse all link and try to find the lowest cost 
int greedy(){
  //seeing whether node choose other path
  int flag=0;

  for (int i=1; i<nodeCnt; i++){
    struct lnode *tmp=node[i].link;
    int tmp_w, tmp_p=node[i].parent;

    while(tmp!=NULL){
      if(tmp->value!=node[i].parent){
        tmp_w=cal_cost(tmp->value, node[i].weight);
        if (tmp_w<node[i].cost){
          node[i].cost=tmp_w;
          tmp_p=tmp->value;
          flag=1;
        }
      }
      tmp=tmp->next;
    }

    //change the weight
    change(i, node[i].weight, 0);
    node[i].parent=tmp_p;
    node[i].level=node[tmp_p].level+1;
    change(i, node[i].weight, 1);
  }

  return flag;
}

int main(){
  int end1, end2;
  struct lnode *tmp;

  //enter data
  scanf("%d %d %d", &nodeCnt, &linkCnt, &packSize);
  for (int i=0; i<nodeCnt; i++){
    nodeLevel[i]=NULL;
    node[i]=(struct nnode) {0, 0, i, 0x3f3f3f3f, 0, NULL};
    scanf("%*d %d", &node[i].weight);
    node[i].ini_weight=node[i].weight;
  }
  //undirection graph
  for (int i=0; i<linkCnt; i++){
    scanf("%*d %d %d", &end1, &end2);
    node[end1].link=insert(node[end1].link, end2);
    node[end2].link=insert(node[end2].link, end1);
  }

  //0 is root
  node[0].cost=0;
  for (int i=0; i<nodeCnt; i++) if(greedy()==0) break;

  //sorting node's level
  maxLevel=0;
  for (int i=0; i<nodeCnt; i++){
    if (maxLevel<node[i].level) maxLevel=node[i].level;
    nodeLevel[node[i].level]=insert(nodeLevel[node[i].level], i); 
  }
  //adding weight of node's subtree
  for (int i=maxLevel; i>=0; i--){
    tmp=nodeLevel[i];
    while(tmp!=NULL){
      node[node[tmp->value].parent].ini_weight+=node[tmp->value].ini_weight;
      tmp=tmp->next;
    }
  }

  //calculus total cost
  int total_cost=0;
  for (int i=1; i<nodeCnt; i++){
    total_cost+=node[i].ini_weight/packSize+1;
    if (node[i].ini_weight%packSize==0) total_cost--;
  }

  //output
  printf("%d %d\n", nodeCnt, total_cost);
  for (int i=0; i<nodeCnt; i++) printf("%d %d\n", i, node[i].parent);

  return 0;
}