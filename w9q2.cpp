#include <iostream>
#include <string>
using namespace std ;

int main()
{
    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        string in;
        cin >> in;
        int first = (in[0] - 'A') * 26 * 26 + (in[1] - 'A') * 26 + (in[2] - 'A');
        int second = (in[4] - '0') * 1000 + (in[5] - '0') * 100 + (in[6] - '0') * 10 + (in[7] - '0');
        if(abs(first - second) <= 100){
            cout << "nice" << endl;
        }
        else{
            cout << "not nice" << endl;
        }
    }
}