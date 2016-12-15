//
// Created by Jakub on 15.12.2016.
//

#ifndef TSP_ANT_H
#define TSP_ANT_H

using namespace std;

#include "Point.h"

class Ant {
public:
    int currentInd;
    int * visited;
    Point * route;

    Ant(int size, Point start);
    //void current();
};


#endif //TSP_ANT_H
