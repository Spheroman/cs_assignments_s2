#include <iostream>

using namespace std ;

int myXor(int a, int b)
{
    return (a | b) & (~a | ~b) ;
}

int main()
{
    int a, b ;
    cin >> a >> b ;
    cout << (~a | ~b) << endl ;
    cout << myXor(a, b) ;
    return 0 ;
}

