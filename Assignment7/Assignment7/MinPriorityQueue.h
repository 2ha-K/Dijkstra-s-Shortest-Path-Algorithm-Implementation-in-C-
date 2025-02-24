//********************************************************************
// ASU CSE310 Assignment #7 Fall 2024
// Name of Author:PO-YI, LIN
// ASU ID:1228434521
// Description: //---- is where you should add your own code
// This represents a min priority queue contains departure city objects. 
//********************************************************************

//include necessary header file here
//----
#include "ArrivalCityList.h"

using namespace std;

//Each node of the graph which is a departure City
struct DepCity
{
    string depCityName;
    double d;
    struct DepCity* pi;
    ArrivalCityList* arrCityList;
};

//class MinPriorityQueue represents a Min-heap that contains DepCity objects.
//The key of each DepCity is its d value.
class MinPriorityQueue
{
private:
    struct DepCity* depCityArr;	        //a DepCity array
    int capacity, size;

public:
    MinPriorityQueue(DepCity* depCityArr, int count);
    ~MinPriorityQueue();

    DepCity* getDepCityArr();
    int getSize();
    int getCapacity();
    int isFound(string oneDepCityName);
    bool decreaseKey(int index, DepCity oneDepCityWithNewDValue);
    bool insert(DepCity oneDepCity);
    void heapify(int index);
    DepCity getHeapMin();
    void extractHeapMin();
    int leftChild(int parentIndex);
    int rightChild(int parentIndex);
    int parent(int childIndex);
    void printHeap();
    void build_min_heap();
};


//*********************************************************
void MinPriorityQueue::printHeap()
{

    cout << "\nHeap size = " << getSize() << "\n" << endl;

    cout << left;
    cout << setw(15) << "Dep. City"
        << setw(12) << "d Value"
        << setw(15) << "PI"
        << "Arrival City List" << endl;
    //----
    //----
    for (int i = 0; i < size; i++)
    {
        cout << setw(15) << depCityArr[i].depCityName
            << setw(12) << depCityArr[i].d
            << setw(15) << (depCityArr[i].pi ? depCityArr[i].pi->depCityName : "NULL")
            << "..." << endl; // Assuming arrival city list details are handled elsewhere
    }
}

//************************************************************
//when you create the dummy node, initialize its d value
bool MinPriorityQueue::insert(DepCity oneDepCity)
{
    //----
    //----
    if (isFound(oneDepCity.depCityName) != -1)
    {
        cout << "City already exists in the heap." << endl;
        return false;
    }

    if (size == capacity)
    {
        cout << "Heap capacity reached. Doubling capacity." << endl;
        capacity *= 2;
        DepCity* newArray = new DepCity[capacity];
        for (int i = 0; i < size; i++)
        {
            newArray[i] = depCityArr[i];
        }
        delete[] depCityArr;
        depCityArr = newArray;
    }

    size++;
    depCityArr[size - 1] = oneDepCity;
    depCityArr[size - 1].d = 2000000000000; // Dummy value initially!!!!!!!!!!
    decreaseKey(size - 1, oneDepCity); // Correct position based on `d` value

    return true;
}

//According to above class definition, define all other functions accordingly
//----
//----
//The constructor initializes the heap with the given capacity and sets the initial size to 0.
MinPriorityQueue::MinPriorityQueue(DepCity* depCityArr, int count)
{
    this->capacity = count;
    this->size = count;
    this->depCityArr = new DepCity[count];
    for (int i = 0; i < count; i++)
    {
        this->depCityArr[i] = depCityArr[i];
    }
}
//The destructor releases the dynamically allocated memory for depCityArr.
MinPriorityQueue::~MinPriorityQueue()
{
    delete[] depCityArr;
    cout << "\nProgram terminate" << endl;
}
//Returns the array of DepCity objects.
DepCity* MinPriorityQueue::getDepCityArr()
{
    return depCityArr;
}
//Returns the current size of the heap.
int MinPriorityQueue::getSize()
{
    return size;
}
//Returns the capacity of the heap.
int MinPriorityQueue::getCapacity()
{
    return capacity;
}
//Checks if a city exists in the heap by its name.Returns the index if found; otherwise, returns - 1.
int MinPriorityQueue::isFound(string oneDepCityName)
{
    for (int i = 0; i < size; i++)
    {
        if (depCityArr[i].depCityName == oneDepCityName)
        {
            return i;
        }
    }
    return -1;
}
//Decreases the d value of a city and repositions it in the heap.
bool MinPriorityQueue::decreaseKey(int index, DepCity oneDepCityWithNewDValue)
{
    if (oneDepCityWithNewDValue.d > depCityArr[index].d)
    {
        cout << "New d value is larger than the current d value." << endl;
        return false;
    }

    depCityArr[index] = oneDepCityWithNewDValue;

    while (index > 0 && depCityArr[parent(index)].d > depCityArr[index].d)
    {
        swap(depCityArr[index], depCityArr[parent(index)]);
        index = parent(index);
    }

    return true;
}
//Removes and returns the city with the smallest d value.
void MinPriorityQueue::extractHeapMin()
{
    if (size < 1)
    {
        cout << "Heap underflow." << endl;
        return;
    }

    depCityArr[0] = depCityArr[size - 1];
    size--;
    heapify(0);
}
//Maintains the min-heap property.
void MinPriorityQueue::heapify(int index)
{
    int l = leftChild(index);
    int r = rightChild(index);
    int smallest = index;

    if (l < size && depCityArr[l].d < depCityArr[smallest].d)
    {
        smallest = l;
    }
    if (r < size && depCityArr[r].d < depCityArr[smallest].d)
    {
        smallest = r;
    }
    if (smallest != index)
    {
        swap(depCityArr[index], depCityArr[smallest]);
        heapify(smallest);
    }
}
//Utility Functions
int MinPriorityQueue::leftChild(int parentIndex)
{
    return 2 * parentIndex + 1;
}

int MinPriorityQueue::rightChild(int parentIndex)
{
    return 2 * parentIndex + 2;
}

int MinPriorityQueue::parent(int childIndex)
{
    return (childIndex - 1) / 2;
}
DepCity MinPriorityQueue::getHeapMin()
{
    if (size <= 0)
    {
        cout << "Error: The heap is empty. Cannot retrieve the minimum." << endl;
        exit(EXIT_FAILURE); 
    }
    return depCityArr[0]; 
}
void MinPriorityQueue::build_min_heap()
{
    for (int i = (size / 2) - 1; i >= 0; i--)
    {
        heapify(i);
    }
}
