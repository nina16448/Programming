#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

void Generate(){ //mode 0 to Generate chunks
    int n, m; //Divide data into n chunks，Generate m chunks for recovery
    int chunk_num, sum; //chunk_num用來記錄目前有幾個chunks，sum紀錄一列含式的和
    chunk_num = 0; //目前chunk數量為0
    char data_str[1000], rec[1000]; //data_str是存原始資料，rec是暫存分割完的字串
    int chunks[1000]; //用來儲存分割完的資料
    scanf("%d%d\n", &n, &m); //輸入2個整數

    int arr[n + m][n + 1]; //Vandermonde matrix
    scanf("%s", data_str);

    int lenth = strlen(data_str); //lenth紀錄資料長度
    int partlen = lenth / n; //計算分割完的字串大小，並存在partlen
    
    for(int i = 0; i < lenth; i += partlen){ //切割字串，一次切partlen的大小
        memset(rec, 0, 1000); 
        for(int j = 0; j < partlen; j++){
            rec[j] = data_str[i + j]; 
        }
        chunks[chunk_num] = atoi(rec); //將分割完的資料轉成整數型態存到陣列裡
        chunk_num++; //每存進去一個資料chunk的數量就會+1
    }

    for(int i = 0; i < n; i++){ //把分割完的資料變成Equations存進二維陣列裡
        for(int j = 0; j <= n; j++){
            if(i == j) arr[i][j] = 1;
            else if(j == n) arr[i][j] = chunks[i];
            else arr[i][j] = 0;
        }
    }

    for(int i = n; i < m + n; i++){ //Use the Vandermonde matrix to generate
        sum = 0;
        for(int j = 0; j <= n; j++){ 
            if(j == n) arr[i][j] = sum; //最後一行放函式的和
            else{
                int item = 1;
                for(int k = 0; k < j; k++){ //計算計次方
                    item *= (i - (n - 1));
                }
                arr[i][j] = item;
            }
            sum += chunks[j] * arr[i][j]; //計算和
        }
    }

    for(int i = 0; i < m + n; i++){ //印出答案
        for(int j = 0; j <= n; j++) printf("%d ", arr[i][j]);
        printf("\n");
    }   
    return;
}

void swap(double **matrices, int A, int B){ // 交換A跟B兩個陣列位置
    if(A == B) return; // 如果A和B是一樣的就不用換
    double *rec = matrices[A];
    matrices[A] = matrices[B];
    matrices[B] = rec;
}


void Reconstruct(){ // 利用高斯消去法重組資料
    int n;
    scanf("%d", &n);

    double **matrices = (double **) malloc(sizeof(double *) * n); //建立二維陣列
    for(int i = 0; i < n; i++)
        matrices[i] = (double *) malloc(sizeof(double) * (n + 1));

    for(int i = 0; i < n; i++){
        for(int j = 0; j <= n; j++){
            scanf("%lf", &matrices[i][j]);
        }
    }

    for(int i = 0; i < n; i++){ //高斯消去法，先一行一行看
        for(int j = i; j < n; j++){ //看第i行的第j列
            if(fabs(matrices[j][i]) > 1e-06){ //如果第i行的第j列不為零
                double divisor = matrices[j][i];

                for(int k = 0; k <= n; k++){ //把第i行的第j列變成1，所以將整列除以第i行的第j列
                    matrices[j][k] /= divisor;
                }
                swap(matrices, j, i); //為了變單位矩陣，把第j行換去第i行，就會變成第i行第i列為1
                
                for(int k = 0; k < n; k++){ //從最上面開始往下找，把第i行除了第i列的元素以外全部變為0
                    if(k == i) continue; //如果是第i列就跳過
                    if(fabs(matrices[k][i]) > 1e-06){ //當第k列第i行不為0時，就把它減到0
                        double times = matrices[k][i]; 
                        for(int l = 0; l <= n; l++){
                            matrices[k][l] -= matrices[i][l] * times;
                        }
                    }
                }
            }
        }
    }

    for(int i = 0; i < n; i++){ //輸出最後一行
        if(fabs(matrices[i][n]) < 1e-06) printf("0"); //避免浮點數會有輸出-0情況
        else printf("%.0f", matrices[i][n]);
    }
}

int main(){
    int mode;
    scanf("%d", &mode); 
    if(!mode) Generate(); // 建立複製資料
    else Reconstruct(); // 還原資料
    
    return 0;
} 
