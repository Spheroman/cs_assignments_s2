#include <iostream>

using namespace std;

unsigned int reverse(unsigned int n) {
    unsigned int r = 0;
    while (n > 0) {
        r = r * 10 + n % 10;
        n /= 10;
    }
    return r;
}

class number {
public:
    unsigned int value;
    number(unsigned int v) { value = v; }

    bool is_palindrome() const { return value == reverse(value); }

    int palindrome_steps() {
        int i = 1;
        this->value += reverse(this->value);
        while (!is_palindrome()) {
            this->value += reverse(this->value);
            i++;
        }
        return i;
    }
};

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        unsigned int v;
        cin >> v;
        number num = v;
        cout << num.palindrome_steps() << " " << num.value << endl;
    }
    return 0;
}