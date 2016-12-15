//
// Created by Jakub on 15.12.2016.
//

//#include <cstdlib>
//#include <ctime>
//#include <cmath>
//#include <iostream>
//#include <cmath>
#include "Ant.h"

Ant::Ant(int size, Point start) {
    currentInd = 0;
    visited = new int[size+1];
    route = new Point[size+1];

    for (int i = 1; i <= size; i++)
        visited[i] = 0;

    route[0] = start;

    visited[start.getId()] = 1;
}

/*
void Ant::current() {
    cout << route[currentInd].getId() << " " << route[currentInd].getX() << endl;
}
*/