#include <iostream>
#include <string>
using namespace std ;

void what(int a[], int n)
{
    bool f ;
    int i = 1, j, k, x, y, z ;

    loop1 :
    f = ((i - n) == 0) ;
    if(f) goto out ;
    k = a[i] ;
    j = i - 1 ;

    loop2 :
    x = j >= 0 ;
    y = (a[j] - k) > 0 ;
    z = x & y ;
    if(!z) goto loop1cond ;
    a[j + 1] = a[j] ;
    j-- ;
    goto loop2 ;

    loop1cond :
    a[j + 1] = k ;
    i++ ;
    goto loop1 ;

    out :
    return ;
} // do not delete this function


// insertion sort
void reDo(int *arr, int n)
{
    int i = 1, idx, cur;
    while (i - n != 0) {
        cur = arr[i] ;
        idx = i - 1 ;
        while (idx >= 0 && arr[idx] - cur > 0) {
            arr[idx + 1] = arr[idx] ;
            idx-- ;
        }
        arr[idx + 1] = cur ;
        i++ ;
    }
}
