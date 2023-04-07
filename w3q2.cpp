#include <iostream>
#include <string>

using namespace std;

int main(){
    string in1, in2;
    cin >> in1 >> in2;
    if (in2.find(in1) != string::npos){
        cout << "Yes";
    }
    else{
        cout << "No";
    }
}