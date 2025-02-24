//********************************************************************
// ASU CSE310 Assignment #7 Fall 2024
// Name of Author:PO-YI, LIN
// ASU ID:1228434521
// Description: //---- is where you should add your own code
// This represents a linked list of arrival cities.
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//struct ArrCity represents an arrival city information with
//distance info. from a specific departure city
struct ArrCity
{
    string arrCityName;
    double distance;
    struct ArrCity* next;
};

//class ArrivalCityList is a linked list of ArrCity
class ArrivalCityList
{
private:
    struct ArrCity* head;

public:
    ArrivalCityList();
    ~ArrivalCityList();
    ArrCity* getHead();
    ArrCity* findArrCity(string oneCity);
    bool addArrCity(string oneCity, double distance);
    void printArrCityList();
    double getDistance(string oneCity);
};

//*******************************************************************
//ArrCity* findArrCity(string oneCity);
//A function to find whether the parameterized city is inside the LinkedList or not.
//returns a pointer that points to the city if it exist, otherwise return NULL

//*******************************************************************
//bool addArrCity(string oneCity, double distance);
//Creates a new ArrCity object and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the ArrCities
//Note: you cannot insert duplicated ArrCity
//Return value: true if it is successfully inserted and false in case of failures.



//According to above class definition, define all functions accordingly
//----
//----
//This is the contructor, it creates an empty linked list.
ArrivalCityList::ArrivalCityList() {
    head = nullptr;
}
//This is the destructor.
ArrivalCityList::~ArrivalCityList() {
    ArrCity* current = head;
    while (current != nullptr) {
        ArrCity* temp = current;
        current = current->next;
        delete temp;
    }
}
//This is the accessor for the only instance variable head
ArrCity* ArrivalCityList::getHead() {
    return head;
}
//Find whether the parameterized city is inside the LinkedList or not. It returns a pointer that points to the city if it exist, otherwise it return NULL
ArrCity* ArrivalCityList::findArrCity(string oneCity) {
    ArrCity* current = head;
    while (current != nullptr) {
        if (current->arrCityName == oneCity) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
//Given an arrival city's name and its distance form the specific departure city, this function creates a new ArrCity object and add it inside the linked list and return true if it is added succucessfully, otherwise it return false.
bool ArrivalCityList::addArrCity(string oneCity, double  distance) {
    if (findArrCity(oneCity) != nullptr) {
        // City already exists, no duplicates allowed
        return false;
    }

    // Create a new node
    ArrCity* newCity = new ArrCity;
    newCity->arrCityName = oneCity;
    newCity->distance = distance;
    newCity->next = nullptr;

    // Insert at the correct position
    if (head == nullptr || head->arrCityName > oneCity) {
        // Insert at the head
        newCity->next = head;
        head = newCity;
    }
    else {
        // Find the insertion point
        ArrCity* current = head;
        while (current->next != nullptr && current->next->arrCityName < oneCity) {
            current = current->next;
        }
        newCity->next = current->next;
        current->next = newCity;
    }

    return true;
}
//This function print all arrival city's info from the head to tail!!!!!!!!!!!!
void ArrivalCityList::printArrCityList() {
    ArrCity* current = head;
    if (current == nullptr) {
        cout << "Arrival city list is empty";
    }
    while (current != nullptr)
    {
        cout << current->arrCityName << "(" << fixed << setprecision(2)
            << current->distance << "), ";
        current = current->next;
    }
    cout << endl;
}

double ArrivalCityList::getDistance(string oneCity) {
    ArrCity* current = head;
    while (current != nullptr) {
        if (current->arrCityName == oneCity) {
            return current->distance; 
        }
        current = current->next;
    }
    return 2000000000000;  
}

