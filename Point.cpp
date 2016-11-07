//
// Created by rozwad on 07.11.16.
//

#include "Point.h"
#include <cmath>

Point::Point() : id(0), x(0), y(0) {}

Point::Point(int id, int x, int y) : id(id), x(x), y(y) {}

int Point::getId() const {
    return id;
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

double distance(const Point &a, const Point &b) {
    return hypot(a.getX() - b.getX(), a.getY() - b.getY());
}

std::ostream &operator<<(std::ostream &stream, const Point &point) {
    stream << point.getId() << " " << point.getX() << " " << point.getY();
    return stream;
}

std::istream &operator>>(std::istream &stream, Point &point) {
    stream >> point.id >> point.x >> point.y;
    return stream;
}
