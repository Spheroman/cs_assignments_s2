#include <cmath>

class Point2D {
private:
    double x;
    double y;

public:
    Point2D() : x(0), y(0) {}

    Point2D(const Point2D& point) : x(point.x), y(point.y) {}

    Point2D(double X, double Y) : x(X), y(Y) {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }
};

class Vector2D {
private:
    double i;
    double j;

public:
    Vector2D() : i(0), j(0) {}

    Vector2D(const Vector2D& v) : i(v.i), j(v.j) {}

    Vector2D(double I, double J) : i(I), j(J) {}

    Vector2D(const Point2D& start, const Point2D& end) {
        i = end.getX() - start.getX();
        j = end.getY() - start.getY();
    }

    double getI() const {
        return i;
    }

    double getJ() const {
        return j;
    }

    Vector2D scale(double ratio) const {
        return Vector2D(i * ratio, j * ratio);
    }
};