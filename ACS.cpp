//
// Created by Jakub on 15.12.2016.
//

#include <iostream>
#include <set>
#include <vector>
#include <cmath>
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

int discreteRandom(vector< pair<int, double> > probs) {
    double random = (double)rand() / RAND_MAX;

    double last = 0;
    for (auto &item: probs) {
        item.second += last;
        last = item.second;
        if (random < item.second) {
            return item.first;
        }
    }
    throw 3; // it should never happen
}

void findNext(Ant &ant) {

    int qq = rand() % 1000;
    int nextInd = 0;

    if (qq <= q) {
        // idź do całkowicie losowo wybranego nieodwiedzonego wierzchołka
        vector<int> unvisited;
        for (int i = 1; i <= n; i++) {
            if (ant.visited[i]) continue;
            unvisited.push_back(i);
        }
        nextInd = unvisited[rand()%unvisited.size()];
    } else {
        // kieruj się feromonami
        vector< pair<int, double> > probs;
        double totalProb = 0;
        int currentId = ant.route[ant.currentInd].getId();
        for (int i = 1; i <= n; i++) {
            if (ant.visited[i]) continue;
            double prob = pow(phero[i][currentId], alpha) * pow(1.0 / distance(points[i], points[currentId]), beta);
            totalProb += prob;

            probs.emplace_back(i, prob);
        }
        for (auto &item: probs) {
            item.second /= totalProb;
        }
        nextInd = discreteRandom(probs);
    }

    if (nextInd == 0) {
        throw 0;
    }

    cout << "Mrówka idzie do " << nextInd << endl; // test

    ant.distance += distance(points[ant.route[ant.currentInd].getId()], points[nextInd]);
    ant.currentInd++;
    ant.route[ant.currentInd] = points[nextInd];
    ant.visited[nextInd] = 1;
}

void localEvaporate(){ // chyba
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            phero[i][j] *= (1 - fi);
        }
    }
}

void localUpdate(Ant &ant){ // dla kazdej mrówki
    int curr = ant.route[ant.currentInd].getId();
    int prev = ant.route[ant.currentInd-1].getId();

    phero[curr][prev] += (fi * p); // opcja 2. (ACS)
    phero[prev][curr] += (fi * p);
}

double routeTotal(Ant &ant){
    return ant.distance;
}

void globalEvaporate(){
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= n; j++){
            phero[i][j] *= (1 - alpha);
        }
    }
}

void globalUpdate(vector<Ant> ants){
    double best = routeTotal(ants[0]);
    Point *bestRoute = ants[0].route;
    for (auto &a : ants){
        double route = routeTotal(a);
        if (route < best){
            best = route;
            bestRoute = a.route;
        }
    }
    for (int i = 1; i < n; i++){
        phero[bestRoute[i].getId()][bestRoute[i-1].getId()] += (alpha * 1.0/best);
        phero[bestRoute[i-1].getId()][bestRoute[i].getId()] += (alpha * 1.0/best);
    }
    phero[bestRoute[0].getId()][bestRoute[n-1].getId()] += (alpha * 1.0/best);
    phero[bestRoute[n-1].getId()][bestRoute[0].getId()] += (alpha * 1.0/best);

    cout << "Shortest route length: " << best << endl;
    cout << "Shortest route: " << endl;
    for (int i = 0; i < n; i++){
        cout << bestRoute[i].getId() << " " << bestRoute[i].getX() << " " << bestRoute[i].getY() << endl;
    }
}



int main() {
    srand(time(NULL));


    cin >> n;
    if (n < 2) {
        cerr << "Należy podać co najmniej dwa punkty!" << endl;
        return -1;
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

    while (cities.size() < (a * n))
        cities.insert(rand()%n + 1);

    cout << "Liczba miast początkowych: " << cities.size() << endl;



    vector<Ant> ants;

    // wybranie miasta początkowego dla każdej mrówki
    for (int city: cities){
        ants.emplace_back(n, points[city]);
    }

    for (int i = 0; i < n-1; i++) {
        // szukana ścieżka ma długość równą liczbie miast

        for (auto &ant : ants) {
            findNext(ant);
        }

        localEvaporate();

        for (auto &ant : ants){
            localUpdate(ant);
        }
    }

    cout << "Loop is over" << endl;

    globalEvaporate();
    globalUpdate(ants);

    //i to wszystko w petli

    //nie zrobilem zwalniania pamieci

    delete points;

    return 0;
}
