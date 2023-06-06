#include <iostream>
#include <string>
using namespace std ;

int check(string in, int len){
    int ret = 0;
    for(int i = 0; i < len; i++){
        for(int x = i; x < len; x++){
            if(in[i] > in[x]){
                ret++;
            }
        }
    }
    return ret;
}

int main()
{
    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        cin;
        int a, b;
        cin >> a >> b;
        string in[b];
        for(int j = 0; j < b; j++){
            cin >> in[j];
        }
        for(int j = 1; j < b; j++){
            for(int x = 0; x < b - j; x++){
                if(check(in[x], a) > check(in[x+1], a)){
                    string temp = in[x];
                    in[x] = in[x+1];
                    in[x+1] = temp;
                }
            }
        }
        for(int j = 0; j < b; j++){
            cout << in[j] << endl;
        }
        cout << endl;

    }
}