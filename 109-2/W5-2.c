/*  probID: W5-2-BinarySearch  */

int BinarySearch( int A[], int n, int k ){
    int L = -1, R = n, mid;
    while(L < R - 1){
        mid = (L + R) / 2;
        if(A[mid] >= k) R = mid;
        else L = mid;
    }
    return R;
}