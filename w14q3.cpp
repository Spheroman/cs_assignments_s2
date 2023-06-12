#include <iostream>
#include <cmath>
#include <string>

using namespace std;

template < typename T >
T *sort(T *array, int n){
    for (int i = 0; i < n-1; i++)
        if(array[i] > array[i+1]){
            T tmp = array[i];
            array[i] = array[i+1];
            array[i+1] = tmp;
            i-=2;
        }
    return array;
}

int main(){
    int i[] = {4, 8, 4, 3, 2, 2, 1, 7};
    int *a = sort<int>(i ,7);
    for(int n = 0; n < 7; n++){
        cout << a[n] << endl;
    }
}