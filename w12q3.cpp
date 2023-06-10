#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int calc(int a, int b, int c){
    return (a-b-c)/2;
}


int main(){
    int s;
    cin >> s;
    int nums[9][9];
    for(; s > 0; s--){
        for (int i = 0; i < 5; i++){
            for (int j = 0; j <= i; j++){
                cin >> nums[i*2][j*2];
            }
        }
        for (int i = 0; i < 4; i++){
            for (int j = 0; j <= i; j++){
                nums[i*2+2][j*2+1] = calc(nums[i*2][j*2], nums[i*2+2][j*2], nums[i*2+2][j*2+2]);
                nums[i*2+1][j*2] = nums[i*2+2][j*2+1] + nums[i*2+2][j*2];
                nums[i*2+1][j*2+1] = nums[i*2+2][j*2+1] + nums[i*2+2][j*2+2];
            }
        }
        for (int i = 0; i < 9; i++){
            for (int j = 0; j <= i; j++){
                cout << nums[i][j];
                if (j != i)
                    cout << " ";
            }
            cout << endl;
        }
    }
}