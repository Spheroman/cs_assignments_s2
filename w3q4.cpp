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
    void print(){
        for (int i = 0; i < xl; i++){
            for (int j = 0; j < yl; j++){
                a[i][j].print();
                cout << " ";
            }
            cout << endl;
        }
    }
    fraction determinant(){
        if (xl != yl){
            cout << "Not a square matrix";
            return {0};
        }
        if (xl == 1){
            return a[0][0];
        }
        if (xl == 2){
            return a[0][0].mul(a[1][1]).sub(a[0][1].mul(a[1][0]));
        }
        fraction ret(0);
        for (int i = 0; i < xl; i++){
            matrix b(xl - 1, yl - 1);
            for (int j = 0; j < xl - 1; j++){
                for (int k = 0; k < yl - 1; k++){
                    b.set(j, k, a[j + (j >= i)][k + (k >= 0)]);
                }
            }
            fraction c = b.determinant();
            if (i % 2 == 0){
                ret.add(c.mul(a[i][0]));
            }
            else{
                ret.sub(c.mul(a[i][0]));
            }
        }
        return ret;
    }
    matrix transpose(){
        matrix ret(yl, xl);
        for (int i = 0; i < xl; i++){
            for (int j = 0; j < yl; j++){
                ret.set(j, i, a[i][j]);
            }
        }
        return ret;
    }

    matrix inverse(){
        if (xl != yl){
            cout << "Cannot produce an inverse matrix.";
            exit(0);
        }
        matrix ret = this->transpose();
        fraction det = ret.determinant();
        if (det.equal({0})){
            cout << "Cannot produce an inverse matrix.";
            exit(0);
        }
        for(int i = 0; i < xl; i++){
            for(int j = 0; j < yl; j++){
                matrix b(xl - 1, yl - 1);
                for (int k = 0; k < xl - 1; k++){
                    for (int l = 0; l < yl - 1; l++){
                        b.set(k, l, a[k + (k >= i)][l + (l >= j)]);
                    }
                }
                ret.set(i, j, b.determinant());
                if ((i + j) % 2 == 1){
                    ret.a[i][j].numerator *= -1;
                }
            }
        }
        return ret.div(det).transpose();
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    cin.ignore();
    matrix a(n, m);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            int x;
            cin >> x;
            cin.ignore();
            a.set(i, j, x);
        }
    }
    a.transpose().print();
    cout << endl;
    a.inverse().print();
    return 0;
}