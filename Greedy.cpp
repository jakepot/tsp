//
// Created by rozwad on 15.11.16.
//

#include <iostream>
#include <list>
#include <limits>
#include "Point.h"
using namespace std;

list<Point>::iterator find_closest(list<Point> &points, Point &start, double &segment) {
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
    segment = closest_distance;
    return closest;
}

double greedy(Point points_array[], int n) {
    double total = 0.0;
    cout << n << endl;
    list<Point> points(points_array, points_array+n);
    auto it = points.begin();
    Point point = *it;
    Point first = point; // copy
    points.erase(it);
    cout << point << endl;

    int i = 1;
    double segment;
    while (!points.empty()) {
        auto closest = find_closest(points, point, segment);
        point = *closest;
        cout << point << endl;
        points.erase(closest);
        total += segment;
    }
    // return to the beginning
    total += distance(point, first);

    return total;
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
    double path = greedy(points, n);
    cout << "Długość ścieżki: " << path << endl;

    delete points;

    return 0;
}
