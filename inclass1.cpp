#include <iostream>

using namespace std;

class Rectangle {
private:
    int length;
    int width;
public:
    Rectangle(int len, int wid) {
        length = len;
        width = wid;
    }

    void printArea() {
        cout << "Area: " << length * width << endl;
    }

    void printPerimeter() {
        cout << "Perimeter: " << 2 * (length + width) << endl;
    }
};

class Square : public Rectangle {
public:
    Square(int side) : Rectangle(side, side) {}
};

int main() {
    Rectangle rect(4435, 553);
    rect.printArea();
    rect.printPerimeter();

    Square sq(53);
    sq.printArea();
    sq.printPerimeter();

    return 0;
}
