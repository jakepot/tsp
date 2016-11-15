//
// Created by rozwad on 15.11.16.
//

#include <iostream>
#include <list>
#include <limits>
#include "Point.h"
using namespace std;

list<Point>::iterator find_closest(list<Point> &points, Point &start) {
    auto it = points.begin();
    auto closest = it;
    double closest_distance = distance(start, *closest);
    double dist;

    for (++it; it != points.end(); ++it) {
        dist = distance(start, *it);
        if (dist < closest_distance) {
            closest = it;
            closest_distance = dist;
        }
    }
    return closest;
}

void greedy(Point points_array[], int n) {
    cout << n << endl;
    list<Point> points(points_array, points_array+n);
    auto it = points.begin();
    Point point = *it;
    points.erase(it);
    cout << point << endl;

    int i = 1;
    while (!points.empty()) {
        auto closest = find_closest(points, point);
        point = *closest;
        cout << point << endl;
        points.erase(closest);
    }
}

int main() {
    int n;
    Point *points;

    cin >> n;
    if (n < 2) {
        cerr << "Należy podać co najmniej dwa punkty!" << endl;
    }
    points = new Point[n];

    for (int i=0; i<n; i++) {
        cin >> points[i];
    }
    greedy(points, n);

    delete points;

    return 0;
}
