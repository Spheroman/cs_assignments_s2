#include <iostream>
#include <string>
using namespace std ;

bool prime(int in){
    if (in == 1){
        return false;
    }
    for(int i = 2; i < in; i++){
        if (in % i == 0){
            return false;
        }
    }
    return true;
}

int main()
{
    int in;
    while(cin >> in){
        if (in <= 1 || in >= 1000000)
            break;
        int reverse = 0;
        int temp = in;
        while(temp != 0){
            reverse = reverse * 10 + temp % 10;
            temp /= 10;
        }
        if (prime(in) && prime(reverse) && in != reverse){
            cout << in << " is emirp." << endl;
        }
        else if (prime(in)){
            cout << in << " is prime." << endl;
        }
        else{
            cout << in << " is not prime." << endl;
        }
    }
}