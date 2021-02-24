/*  probID: W4-2-Expression  */

int Calculation(int n, int type[], int integers[], char symbols[], int begin, int end);
int expr_evaluation( int n, int type[], int integers[], char symbols[] );

int expr_evaluation( int n, int type[], int integers[], char symbols[] ){
    return Calculation(n, type, integers, symbols, 0, n - 1);
}

int Calculation(int n, int type[], int integers[], char symbols[], int start, int last){
    int flag = 0, final = -1, record = 0, cnt = 0, begin = start, end = last;
    for(int i = begin; i < end; i++){
        if(symbols[i] == '(') record++;
        if(record == 0) cnt++;
        if(symbols[i] == ')') record--;
    }
    if(cnt == 0 && (symbols[begin] == '('&& symbols[end - 1] == ')')){
        begin += 1;
        end -= 1;
    }
    record = 0;
    if(begin + 1 == end) return integers[begin];

    for(int i = begin; i < end; i++){
        if(symbols[i] == '(') record++;
        if(symbols[i] == ')') record--;
        if(record != 0) continue;

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

    if(flag == 1 || flag == -1)
        return Calculation(n, type, integers, symbols, begin, final) + flag * Calculation(n, type, integers, symbols, final + 1, end);
    if(flag == 0)
        return Calculation(n, type, integers, symbols, begin, final) * Calculation(n, type, integers, symbols, final + 1, end);
    if(flag == 2) 
        return Calculation(n, type, integers, symbols, begin, final) / Calculation(n, type, integers, symbols, final + 1, end);
}
