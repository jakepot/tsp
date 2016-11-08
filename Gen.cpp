//
// Created by corni on 08.11.2016.
//

#include <cstdlib>
#include <ctime>
#include <vector>
#include "Point.h"

std::vector <Point> generate(int n) {
    std::vector <Point> Points;

    srand((unsigned)time(NULL));

    for (int i = 0; i < n; i++){
        Points.push_back(Point(i, rand()%100, rand()%100));
        std::cout << Points[i];
    }

    return Points;
}