#include <iostream>
#include <string>

using namespace std;

bool explainThis(char *s, char *t)
{
    for (; *t && *s ; s += *s == *t++) ;
    return !*s ;
}


int main(){
    string in1, in2;
    cin >> in1 >> in2;
    if (explainThis(&in1[0], &in2[0])){
        cout << "Yes";
    }
    else{
        cout << "No";
    }
}