#include <iostream>
#include <cmath>

using namespace std;

int optimistic(int p, int add, int m){
    if (p == 0)
        return 1;
    int med = (1 << (p - 1)) + add;
    return (m >= med)? 1 + optimistic(p-1, med, m) : optimistic(p-1 , add, m);
}

int pessimistic(int n, int m) {
    if (m == 0)
        return 1;
    if (m % 2 == 1)
        return pow(2, n);
    n++;
    while ((m % 2) == 0 && m > 0) {
        m /= 2;
        n--;
    }
    return pow(2, n) - 1;
}

int main() {
    cout << (2&(-2));
    int i;
    cin >> i;
    for (; i > 0; i--){
        int n, m;
        cin >> n >> m;
        if (n > 31) return -1;
        cout << optimistic(n, 0, m) << " " << pessimistic(n, m) << endl;
    }
}