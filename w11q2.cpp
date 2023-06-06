#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class Subject {
public:
    string name;
    int days;
    Subject() {
        this->name = "";
        this->days = 0;
    }
};

int main() {
    int t, n;
    cin >> t;
    for(int j = 0; j < t; j++){
        cin >> n;
        Subject subjects[n];
        string name;
        for(int i = 0; i < n; i++){
            cin >> subjects[i].name >> subjects[i].days;
        }
        int d;
        cin >> d;
        cin >> name;
        int i = 0;
        for(; i < n; i++){
            if ((subjects[i].name) == name)
                break;
        }
        cout << "Case " << j + 1 << ": ";
        if (i != n)
            if (subjects[i].days > d)
                if (subjects[i].days <= d + 5)
                    cout << "Late" << endl;
                else
                    cout << "Do your own homework!" << endl;
            else
                cout << "Yesss" << endl;
        else{
            cout << "Do your own homework!" << endl;
        }
    }
}