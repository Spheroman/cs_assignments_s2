#include <math.h>
#include <iostream>

using namespace std;

class Point{
private:
    float x;
    float y;
public:
    Point(float x, float y){
        this->x = x;
        this->y = y;
    }
    Point(){
        this->x = 0;
        this->y = 0;
    }
    float getX(){
        return this->x;
    }
    float getY(){
        return this->y;
    }
    void setX(float x){
        this->x = x;
    }
    void setY(float y) {
        this->y = y;
    }
};

class Segment{
private:
    Point point1;
    Point point2;
public:
    Segment(Point point1, Point point2){
        this->point1 = point1;
        this->point2 = point2;
    }
    Segment(){
        this->point1 = Point();
        this->point2 = Point();
    }
    float getLength(){
        float x1 = this->point1.getX();
        float y1 = this->point1.getY();
        float x2 = this->point2.getX();
        float y2 = this->point2.getY();
        return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    }
};

class Shape{
protected:
    int n;
    Segment* segments;
public:
    virtual float area() = 0;
    virtual float getPerimeter(){
        float perimeter = 0;
        for(int i=0;i<n;i++){
            perimeter += segments[i].getLength();
        }
        return perimeter;
    }
};

class Triangle: public Shape{
public:
    Triangle(Segment* segments){
        this->n = 3;
        this->segments = segments;
    }
    float area() override{
        float a = this->segments[0].getLength();
        float b = this->segments[1].getLength();
        float c = this->segments[2].getLength();
        float p = (a+b+c)/2;
        return sqrt(p*(p-a)*(p-b)*(p-c));
    }
};

class Square: public Shape{
public:
    Square(Segment* segments){
        this->n = 4;
        this->segments = segments;
    }
    float area() override{
        float a = this->segments[0].getLength();
        return a*a;
    }
};//
// Created by Jack Wen on 5/31/2023.
//
