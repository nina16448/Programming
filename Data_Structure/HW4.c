#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

unsigned int Hash_Function(unsigned int ID, unsigned int p, unsigned int m){ //Hash function 分兩個情況處理
    if(p >= 97){ //當p >= 97時 則mod更大的質數 不然mod小的反而結果更容易相同
        ID += ID / (unsigned int)49669;
        ID %= (unsigned int)49669;
        ID += ID / (unsigned int)45533;
        ID %= (unsigned int)45533;
        ID += ID / (unsigned int)25097;
        ID %= (unsigned int)25097;
        ID = ID % p;
        return ID % m;
    }
    ID += ID / (unsigned int)97;
    ID %= (unsigned int)97;
    ID %= (unsigned int)71;
    ID %= (unsigned int)67;
    ID %= (unsigned int)41;
    ID = ID % p;
    return ID % m;
}

int main(){
    int num = 0;
    unsigned int p, m, n, ID;
    //p是存測資給的質數
    //m是存測資給m bit
    //n是有幾個userID
    //ID是存輸入的userID
    scanf("%u%u%u", &p, &m, &n);
    unsigned char* rec = malloc(sizeof(unsigned char) * (m / 8 + 1)); //最少需要m/8個byte的空間

    for(unsigned int i = 0; i <= m / 8; i++) //初始化
        rec[i] = 0;
    
    for(int i = 0; i < n; i++){
        scanf("%u", &ID);
        if(ID < m) num++;
        unsigned int index = Hash_Function(ID, p, m); //用來存經過hash算式計算後要存放的位置
        
        if(!(rec[index / 8] & (1 << (index % 8)))){ //用AND來判斷那格有沒有被填過 有填過則 1 AND 1 會回傳1 其餘則皆為0
            rec[index / 8] |= 1 << (index % 8); //用OR來將第index / 8個rec的第index % 8個位元設為1
            printf("%d %d\n", ID, 1);
        }
        else 
            printf("%d %d\n", ID, 0);
    }
    //if(m > 8000) printf("asds");
    return 0;
}