//********************************************************************
// ASU CSE310 Assignment #7 Fall 2024
// Name:PO-YI, LIN
// ASU ID:1228434521
// Description: //---- is where you should add your own code
//********************************************************************

//include necessary header file here
//----
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Graph.h" 

using namespace std;

void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList);
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance);     //**optional

int main()
{
   int count;       //number of nodes
   string oneLine, sourceCityName;
   string answer = "yes";       //a variable to decide whether to run Dijkstra multiple times or not

   //cout << "Enter number of cities: ";
   cin >> count;
   cin.ignore(20, '\n');

   //For each line, we will create an ArrivalCityList(which is a linked list) for a specific departure city.
   //It represents all its reachable arrival cities with distance info.
   //Here we use an array of DepCity to store them
   DepCity* depCityArr = new DepCity[count];

   //Initialize depCityArr. Set each node's d value to be very large 20000.0
   //initialize each arrival city list
   for(int i = 0; i< count; i++)
   {
      depCityArr[i].d = 20000.0 + i;      //**this is to make sure each node has different d value
      //----
      //----
      depCityArr[i].arrCityList = new ArrivalCityList();
      depCityArr[i].pi = nullptr;
   }

   //get input line by line and create the depCityArr
   for(int i = 0; i< count; i++)
   {
      getline(cin, oneLine);
      //----
      //----
      getCityInfo(oneLine, depCityArr[i].depCityName, depCityArr[i].arrCityList);
   }

  //create a Graph object
  //----

    // Create MinPriorityQueue and Graph objects
    MinPriorityQueue* cityHeap = new MinPriorityQueue(depCityArr, count);
    Graph graph(count, cityHeap);

   //print the graph adjacency list before running Dijkstra algorithm
   cout << "\nPrint the graph adjacency list before running Dijkstra algorithm" << endl;
  //----
   cout << "\nHeap size = " << count << endl << endl;
   graph.printGraph();

   //Next you need to design a sentinel value controlled while loop base on 'answer'
   //If user answer is 'yes', get source city name, run Dijkstra algorithm, print
   //shortest path, then ask whether user want to continue the algorithm or not.
   while (answer == "yes")
   {    

       cout << "\nEnter the source city name: "<<endl;
       cin >> sourceCityName;

       graph.dijkstra(sourceCityName);
       graph.printDijkstraPath(sourceCityName);

       cout << "\nFind shortest path for another departure city(yes or no): "<<endl;
       cin >> answer;
   }

   // Clean up
   delete[] depCityArr;
   cout << "\nProgram terminate";
   return 0;
}

//************************************************************************
//Given one line in input file, this function extract tokens and get departure city
//name and its arrival cities info.
void getCityInfo(string oneLine, string& depCityName, ArrivalCityList* arrCityList)
{
   //----
   //----
    stringstream ss(oneLine);
    string token;

    // First token is the departure city name
    getline(ss, depCityName, ',');

    // Remaining tokens are arrival city info
    while (getline(ss, token, ','))
    {
        // Skip empty tokens
        if (token.empty()) {
            continue;
        }

        string arrCityName;
        double distance;
        getArrCityInfo(token, arrCityName, distance);
        arrCityList->addArrCity(arrCityName, distance);
    }
}

//****************************************************************************
//Given one arrival city info. format of, such as Z(60.2), this function
//extract arrival city name 'Z' and distance 60.2 from it.
//this function is optional. Feel free to extract tokens using your own way
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance)
{
    size_t pos1 = oneArrCityInfo.find('(');
    size_t pos2 = oneArrCityInfo.find(')');

    // Extract city name and distance
    arrCityName = oneArrCityInfo.substr(0, pos1);
    distance = stod(oneArrCityInfo.substr(pos1 + 1, pos2 - pos1 - 1));
}