//
// Created by rozwad on 07.11.16.
//

#ifndef TSP_POINT_H
#define TSP_POINT_H

#include <iostream>

class Point {
    int id;
    int x;
    int y;
public:
    Point();
    Point(int id, int x, int y);

    int getId() const;
    int getX() const;
    int getY() const;

    friend std::ostream& operator<< (std::ostream &stream, const Point &point);
    friend std::istream& operator>> (std::istream &stream, Point &point);
};

double distance(const Point &a, const Point &b);

#endif //TSP_POINT_H
