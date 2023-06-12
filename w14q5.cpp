#include <iostream>
#include <cmath>

using namespace std;

class Line{
public:
    double x1, y1, x2, y2;
    bool valid = true;

    Line(){
        x1 = 0;
        y1 = 0;
        x2 = 0;
        y2 = 0;
        valid = false;
    }

    Line(double x1, double y1, double x2, double y2){
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }

    double length(){
        return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

    double slope(){
        return (y2 - y1) / (x2 - x1);
    }

    void cut(int y){
        double x = (y - y1) / slope() + x1;
        x2 = x;
        y2 = y;
    }
};

class Peaks{
public:
    int x, y;
    Peaks *next;
    Peaks(int x, int y){
        this->x = x;
        this->y = y;
        next = nullptr;
    }

    Peaks(int x, int y, Peaks *next){
        this->x = x;
        this->y = y;
        this->next = next;
    }

    Peaks add(int x, int y){
        Peaks *cur = this;
        while(cur->next != nullptr && cur->next->x < x)
            cur = cur->next;
        if(cur->x == x){
            cur->y = y;
            return *this;
        }
        cur->next = new Peaks(x, y, cur->next);
        return *this;
    }

    Line* lineify(){
        Peaks *cur = this;
        int max = 0;
        while(cur != nullptr){
            if(cur->y > max)
                max = cur->y;
            cur = cur->next;
        }
        cur = this;
        while(cur->y != max){
            cur = cur->next;
        }

        Line *lines = new Line[1000];
        int i = 0;
        while(cur->next != nullptr){
            lines[i] = Line(cur->x, cur->y, cur->next->x, cur->next->y);
            if(lines[i].slope()>=0)
                i--;
            cur = cur->next;
            i++;
        }
        return lines;
    }

};

int main() {
    int c;
    cin >> c;
    for(; c > 0; c--){
        int n;
        cin >> n;
        Peaks *peaks = new Peaks(0, 0);
        for(int i = 0; i < n; i++){
            int x, y;
            cin >> x >> y;
            peaks->add(x, y);
        }
        Line *lines = peaks->lineify();
        double tot = 0;
        for(int i = 0; i < n && lines[i].valid; i++){
            if (i < n - 1 && lines[i].valid)
                lines[i].cut(lines[i + 1].y1);
            tot += lines[i].length();
        }
        cout << tot;
        if (c > 1)
            cout << endl;
    }
}