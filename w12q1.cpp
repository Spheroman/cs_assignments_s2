#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int* getPrimes(int n){
    int* primes = new int[n + 1];
    primes[0] = 1;
    primes[1] = 2;
    int i = 2;
    for (int j = 3; j <= n; j++){
        bool isPrime = true;
        for (int k = 1; k < i; k++){
            if (j % primes[k] == 0){
                isPrime = false;
                break;
            }
        }
        if (isPrime)
            primes[i++] = j;
    }
    primes[n] = i;
    return primes;
}

int main(){
    int a, b;
    while (cin >> a >> b){
        if(a < 0 || b < 0 || a > 1000 || b > a)
            break;
        int* primes = getPrimes(a);
        int numprimes = primes[a];
        int min = 0, max = 0;
        min = numprimes / 2 - b + numprimes % 2;
        max = numprimes / 2 + b;
        if (min < 0)
            min = 0;
        if (max > numprimes)
            max = numprimes;
        cout << a << " " << b << ": ";
        for (; min < max; min++){
            cout << primes[min];
            if (min != max - 1)
                cout << " ";
        }
        cout << endl << endl;
    }

}