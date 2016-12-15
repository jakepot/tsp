//
// Created by Jakub on 15.12.2016.
//

#include <iostream>
//#include <list>
//#include <limits>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <set>
#include <vector>
//#include <iterator>
#include "Point.h"
#include "Ant.h"

using namespace std;

double alpha = 0.5; // global evap.
double beta = 0.5; // (1/dist) pheromone update
double fi = 0.5; // local evap. chyba fi
double p = 1.0; // starting pheromone value
double a = 1.0; // % of ants
int q = 10; // q/1000

int n; // number of cities

Point *points;
double ** phero;

void findNext(Ant &ant) {
    srand(time(NULL));

    int qq = rand() % 1000;

    int nextInd = 0;

    if (qq <= q){
        int s = rand() %(n - ant.currentInd + 1);
        int t = 0;

        for (int i = 1; i <= n; i++){
            if (ant.visited[i] == 0)
                t++;
            if (s == t){
                nextInd = i;
                break;
            }
        }
    }
    else {
        double max = 0;
        for (int i = 1; i <= n; i++) {
            if (ant.visited[i] == 0) {
                //cout << i << endl;
                double s = phero[i][ant.route[ant.currentInd].getId()]
                           * pow(1.0 / distance(points[i], points[ant.route[ant.currentInd].getId()]), beta);
                if (s > max) {
                    max = s;
                    nextInd = i;
                }
            }
        }
    }

    cout << nextInd << endl; // test

    ant.currentInd++;
    ant.route[ant.currentInd] = points[nextInd];
    ant.visited[points[nextInd].getId()] = 1;
}

void localEvaporate(){ // chyba
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            phero[i][j] *= (1 - fi);
        }
    }
}

void localUpdate(Ant ant){ // dla kazdej mrowki
    phero[ant.route[ant.currentInd].getId()][ant.route[ant.currentInd-1].getId()] += (fi * p); // opcja 2. (ACS)
    phero[ant.route[ant.currentInd-1].getId()][ant.route[ant.currentInd].getId()] += (fi * p);
}

double routeTotal(Ant ant){
    double total = 0.0;
    for (int i = 1; i < n; i++){
        total += distance(ant.route[i],ant.route[i-1]);
    }
    total += distance(ant.route[0],ant.route[n-1]);
    return total;
}

void globalEvaporate(){
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            phero[i][j] *= (1 - alpha);
        }
    }
}

void globalUpdate(vector<Ant> ants){
    double best = 1000000.0; // very big number
    Point bestRoute[n];
    for (auto &a : ants){
        double route = routeTotal(a);
        if (route < best){
            best = route;
            //copy(begin(a.route), end(a.route), begin(bestRoute)); // HELP nie przechodzi
        }
    }
    for (int i = 1; i < n; i++){
        phero[bestRoute[i].getId()][bestRoute[i-1].getId()] += (alpha * 1.0/best);
        phero[bestRoute[i-1].getId()][bestRoute[i].getId()] += (alpha * 1.0/best);
    }
    phero[bestRoute[0].getId()][bestRoute[n-1].getId()] += (alpha * 1.0/best);
    phero[bestRoute[n-1].getId()][bestRoute[0].getId()] += (alpha * 1.0/best);

    cout << "Shortest route length: " << best << endl;
    cout << "Shortest route: ";
    for (int i = 0; i < n; i++){
        cout << bestRoute[i].getId() << " -> ";
    }
    cout << bestRoute[0].getId();
}



int main() {
    cin >> n;
    if (n < 2) {
        cerr << "Należy podać co najmniej dwa punkty!" << endl;
    }
    points = new Point[n+1];

    for (int i=1; i<=n; i++) { // points from 1
        cin >> points[i];
    }

    phero = new double*[n];

    for(int i = 1; i <= n; ++i)
        phero[i] = new double[n];

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            phero[i][j] = p;
        }
    }

    // stworzenie mrowek
    set<int> cities;

    srand(time(0));

    while (cities.size() < (a * n))
        cities.insert(rand()%n+1);

    vector<Ant> ants;
    auto it = cities.begin();

    while(it!=cities.end()){
        ants.emplace_back(n, points[*it]);
        it++;
    }

    for (int i = 0; i < n-1; i++){
        for (auto &it1 : ants){
            findNext(it1);
        }
        localEvaporate();
        for (auto &it2 : ants){
            localUpdate(it2);
        }
    }
    //globalEvaporate();
    //globalUpdate(ants);

    //i to wszystko w petli

    //nie zrobilem zwalniania pamieci

    delete points;

    return 0;
}
