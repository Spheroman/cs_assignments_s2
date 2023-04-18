#include <iostream>
#include <string>

using namespace std;

class fraction{
public:
    int numerator;
    int denominator;
    fraction(int n, int d){
        int g = gcd(n, d);
        numerator = n/g;
        denominator = d/g;
    }
    fraction(int n){
        numerator = n;
        denominator = 1;
    }
    fraction(){
        numerator = 0;
        denominator = 1;
    }
    fraction add(fraction f){
        int n = numerator * f.denominator + f.numerator * denominator;
        int d = denominator * f.denominator;
        int g = gcd(n, d);
        numerator = n/g;
        denominator = d/g;
        return *this;
    }
    fraction sub(fraction f){
        int n = numerator * f.denominator - f.numerator * denominator;
        int d = denominator * f.denominator;
        int g = gcd(n, d);
        numerator = n/g;
        denominator = d/g;
        return *this;
    }
    fraction mul(fraction f){
        int n = numerator * f.numerator;
        int d = denominator * f.denominator;
        int g = gcd(n, d);
        numerator = n/g;
        denominator = d/g;
        return *this;
    }
    fraction div(fraction f){
        int n = numerator * f.denominator;
        int d = denominator * f.numerator;
        int g = gcd(n, d);
        numerator = n/g;
        denominator = d/g;
        return *this;
    }
    bool equal(fraction f){
        return numerator * f.denominator == f.numerator * denominator;
    }
    int gcd(int a, int b){
        if (b == 0){
            return a;
        }
        else{
            return gcd(b, a % b);
        }
    }
    void print(){
        int mod = 1;
        if(denominator<0){
            mod = -1;
        }
        if (denominator == 1){
            cout << numerator;
        }
        else{
            cout << numerator*mod << "/" << denominator*mod;
        }
    }
};

class matrix{
public:
    fraction** a;
    int xl, yl;
    matrix(int x, int y){
        xl = x;
        yl = y;
        a = new fraction*[x];
        for(int i = 0; i < x; ++i) {
            a[i] = new fraction[y];
        }
    }
    void set(int x, int y, fraction f){
        a[x][y] = f;
    }
    void set(int x, int y, int n, int d){
        a[x][y] = fraction(n, d);
    }
    void set(int x, int y, int n){
        a[x][y] = fraction(n, 1);
    }
    matrix div(fraction f){
        for (int i = 0; i < xl; i++){
            for (int j = 0; j < yl; j++){
                a[i][j].div(f);
            }
        }
        return *this;
    }

    virtual void print(){
        for (int i = 0; i < xl; i++){
            for (int j = 0; j < yl; j++){
                a[i][j].print();
                cout << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    virtual matrix rotateright(){
        fraction** b = new fraction*[yl];
        for(int i = 0; i < yl; ++i) {
            b[i] = new fraction[xl];
        }
        for (int i = 0; i < xl; i++){
            for (int j = 0; j < yl; j++){
                b[j][xl-i-1] = a[i][j];
            }
        }
        a = b;
        int temp = xl;
        xl = yl;
        yl = temp;
        return *this;
    };

    virtual matrix rotateleft(){
        fraction** b = new fraction*[yl];
        for(int i = 0; i < yl; ++i) {
            b[i] = new fraction[xl];
        }
        for (int i = 0; i < xl; i++){
            for (int j = 0; j < yl; j++){
                b[yl-j-1][i] = a[i][j];
            }
        }
        a = b;
        int temp = xl;
        xl = yl;
        yl = temp;
        return *this;
    };
};

class none : public matrix{
public:
    none() : matrix(0, 0){}
    void print() override{
        cout << "No element in matrix can be printed.\n";
    }
    matrix rotateleft() override{
        cout << "No element in matrix can be rotated.\n";
        return *this;
    }
    matrix rotateright() override{
        cout << "No element in matrix can be rotated.\n";
        return *this;
    }
};

matrix* scan(){
    int n;
    cin >> n;
    cin.ignore();
    if (n == 0){
        return new none();
    }
    matrix *a = new matrix(n, n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int x;
            cin >> x;
            cin.ignore();
            a -> set(i, j, x);
        }
    }
    return a;
}


int main(){
    string in;
    matrix *cur;
    cur = new none();
    while(true){
        getline(cin, in);
        if(in == "scan"){
            cur = scan();
        }
        else if(in == "print"){
            cur->print();
        }
        else if(in == "stop"){
            break;
        }
        else if(in == "rotate left"){
            cur->rotateleft();
        }
        else if(in == "rotate right"){
            cur->rotateright();
        }
        else{
            cout << "unknown\n";
        }
    }
    return 0;
}