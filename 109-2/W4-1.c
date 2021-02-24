/*  probID: W4-1-Expression  */
//#include<stdio.h>

int Calculation(int n, int type[], int integers[], char symbols[], int begin, int end);
int expr_evaluation( int n, int type[], int integers[], char symbols[] );

int expr_evaluation( int n, int type[], int integers[], char symbols[] ){
    
    return Calculation(n, type, integers, symbols, 0, n - 1);
}

int Calculation(int n, int type[], int integers[], char symbols[], int begin, int end){
    if(begin + 1 == end) return integers[begin];
    int flag = 0, final = -1;
    for(int i = begin; i < end; i++){
        if(symbols[i] == '+'){
            final = i;
            flag = 1;
        }
        if(symbols[i] == '-'){
            final = i;
            flag = -1;
        }
        if(flag == 0 || flag == 2){
            if(symbols[i] == '*'){
                final = i;
                flag = 0;
            }
            if(symbols[i] == '/'){
                final = i;
                flag = 2;
            }
        }
    }
    //printf("%d %d\n", flag, final);
    
    if(flag == 1 || flag == -1)
        return Calculation(n, type, integers, symbols, begin, final) + flag * Calculation(n, type, integers, symbols, final + 1, end);
    if(flag == 0)
        return Calculation(n, type, integers, symbols, begin, final) * Calculation(n, type, integers, symbols, final + 1, end);
    if(flag == 2) 
        return Calculation(n, type, integers, symbols, begin, final) / Calculation(n, type, integers, symbols, final + 1, end);
}

/*

int expr_evaluation(int n, int type[], int integers[], char symbols[]);

int main()
{

    int times,n,ans;
    scanf("%d", &times);

    int type[10001];
    int integers[10001];
    char symbols[10001];

    int i, j;
    for(i=0;i<times;i++)
    {

        scanf("%d", &n);

        for(j=0;j<n;j++)
            scanf("%d", &type[j]);
            
        for(j=0;j<n;j++)
            scanf("%d", &integers[j]);
            
        for(j=0;j<n;j++)
            scanf(" %c", &symbols[j]);

        ans = expr_evaluation(n,type,integers,symbols);

        printf("%d\n", ans);

    }
    

    return 0;
}
*/