#include <iostream>
#include <cmath>
#include <string>

using namespace std;


int main(){
    int skyline[5000];
    for(int i = 0; i < 5000; i++)
        skyline[i] = 0;
    int x1, x2, h, cur = 0;
    while(cin >> x1 >> h >> x2){
        if(x2 > cur)
            cur = x2;
        for(int i = x1; i < x2; i++)
            if(skyline[i] < h)
                skyline[i] = h;
    }
    int last = 0;
    for(int i = 0; i < cur; i++){
        if(skyline[i] != last){
            cout << i << " " << skyline[i] << " ";
            last = skyline[i];
        }
    }
    cout << cur << " 0" << endl;
    return 0;
}