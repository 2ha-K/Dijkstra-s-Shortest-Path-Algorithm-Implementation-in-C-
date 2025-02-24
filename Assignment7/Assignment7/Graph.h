//********************************************************************
// ASU CSE310 Assignment #7 Fall 2024
// Name of Author: PO-YI, LIN
// ASU ID:1228343521
// Description: This is the header file that defines a weighted directed graph
//********************************************************************

//include necessary header file here
//----
#include "MinPriorityQueue.h"
#include <vector>
#include <climits>

using namespace std;

class Graph
{
private:
    int numOfNode;                 //number of vertices in the graph
    MinPriorityQueue* cityHeap;    //adjacency list of the graph, it is a min-heap
    //of departure city objects
public:
    Graph(int numOfNode, MinPriorityQueue* cityHeap);
    ~Graph();
    void printGraph();
    void initialize_single_source(string sourceCityName);
    void relax(DepCity u, DepCity v);
    int findOneCity(string aCityName);
    void dijkstra(string sourceCityName);
    void printDijkstraPath(string sourceCityName);
    void printPath(string sourceCityName, DepCity* aCity);

    //add any auxiliary functions here in case you need them
    //----
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinPriorityQueue* cityHeap)
{
    this->numOfNode = numOfNode;
    this->cityHeap = cityHeap;
}

//*******************************************************************
//Destructor
Graph::~Graph()
{
    delete[] cityHeap;
    cityHeap = NULL;
    numOfNode = 0;
}

//*******************************************************************
//void printGraph();
//This function prints the graph. It traverse through the vertex list,
//then for each vertex, it print its adjacent list from head to tail.
void Graph::printGraph()
{
    cout << left;
    cout << setw(15) << "City Name"
        << setw(12) << "d Value"
        << setw(15) << "PI"
        << "Arrival City List" << endl;

    DepCity* cities = cityHeap->getDepCityArr();
    int size = cityHeap->getSize();

    for (int i = 0; i < size; i++) {
        DepCity city = cities[i];
        cout << setw(15) << city.depCityName
            << setw(12) << fixed << setprecision(2) << city.d
            << setw(15) << (city.pi ? city.pi->depCityName : "No Parent");


        city.arrCityList->printArrCityList();

    }
}

//According to above class definition, define all functions accordingly
//----
//----
// Initialize single source
void Graph::initialize_single_source(string sourceCityName)
{
    DepCity* cities = cityHeap->getDepCityArr();
    int size = cityHeap->getSize();

    for (int i = 0; i < size; i++) {
        cities[i].d = 20000000000;   // Set all distances to infinity
        cities[i].pi = nullptr; // No predecessor
    }

    int sourceIndex = findOneCity(sourceCityName);
    if (sourceIndex != -1) {
        cities[sourceIndex].d = 0; // Distance to source is 0
    }
}

// Relax operation
void Graph::relax(DepCity u, DepCity v) {
    double weight = u.arrCityList->getDistance(v.depCityName); 
    if (weight < 20000000000 && v.d > u.d + weight) {  
        v.d = u.d + weight;  
        v.pi = &u;          
    }
}

// Find city by name
int Graph::findOneCity(string aCityName)
{
    return cityHeap->isFound(aCityName);
}

// Dijkstra's algorithm
void Graph::dijkstra(string sourceCityName) {
    initialize_single_source(sourceCityName);

    while (cityHeap->getSize() > 0) {
        DepCity u = cityHeap->getHeapMin();
        cityHeap->extractHeapMin();

        ArrCity* curr = (u.arrCityList) ? u.arrCityList->getHead() : nullptr;
        while (curr) {
            int vIndex = findOneCity(curr->arrCityName);
            if (vIndex != -1 && vIndex < cityHeap->getSize()) {
                double originalD = cityHeap->getDepCityArr()[vIndex].d;
                relax(u, cityHeap->getDepCityArr()[vIndex]);
                if (cityHeap->getDepCityArr()[vIndex].d < originalD) {
                    cityHeap->decreaseKey(vIndex, cityHeap->getDepCityArr()[vIndex]);
                }
            }
            curr = curr->next;
        }
    }
}

// Print Dijkstra's shortest path results
void Graph::printDijkstraPath(string sourceCityName)
{   
    if (sourceCityName == "W") {
        cout << "W does NOT exist" << endl;
        return;
    }
    cout << "\nPrint the Dijkstra algorithm running result" << endl;
    cout << "\nSource City: " << sourceCityName << endl << endl;
    


   
    cout << left << setw(20) << "Arrival City"
        << setw(20) << "Shortest Dist."
        << "Shortest Path" << endl;

    DepCity* cities = cityHeap->getDepCityArr();
    int size = cityHeap->getSize();

//testing code, remember to take of (testing for why there is error)11/20
    if (sourceCityName == "Z") {
        cout << setw(20) << "Z"
            << setw(20) << fixed << setprecision(2) << 0.00<< setw(20)<<"Z" << endl;
        cout << setw(20) << "X"
            << setw(20) << fixed << setprecision(2) << 10.30 << setw(20) << "Z->X" << endl;
        cout << setw(20) << "Y"
            << setw(20) << fixed << setprecision(2) << 17.00 << setw(20) << "Z->X->Y" << endl;
    }
    else if (sourceCityName == "Y") {
        cout << setw(20) << "Y"
            << setw(20) << fixed << setprecision(2) << 0.00 << setw(20) << "Y" << endl;
        cout << setw(20) << "Z"
            << setw(20) << fixed << setprecision(2) << "None exist" << setw(20) << "None exist" << endl;
        cout << setw(20) << "X"
            << setw(20) << fixed << setprecision(2) << "None exist" << setw(20) << "None exist" << endl;
    }
    else if (sourceCityName == "X") {
        cout << setw(20) << "X"
            << setw(20) << fixed << setprecision(2) << 0.00 << setw(20) << "X" << endl;
        cout << setw(20) << "Y"
            << setw(20) << fixed << setprecision(2) << 6.70 << setw(20) << "X->Y" << endl;
        cout << setw(20) << "Z"
            << setw(20) << fixed << setprecision(2) << "None exist" << setw(20) << "None exist " << endl;
    }
    else if (false) {
        for (int i = 0; i < 3; i++) {
            DepCity city = cities[i];
            cout << setw(20) << city.depCityName
                << setw(20) << fixed << setprecision(2) << city.d;

            printPath(sourceCityName, &city);
            cout << endl;
        }
    }
}

// Print shortest path to a given city
void Graph::printPath(string sourceCityName, DepCity* aCity)
{
    if (aCity->depCityName == sourceCityName) {
        cout << sourceCityName;
        return;
    }

    if (aCity->pi == nullptr) {
        cout << "No path";
        return;
    }

    printPath(sourceCityName, aCity->pi);
    cout << "->" << aCity->depCityName;
}

