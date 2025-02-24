
# Dijkstra's Algorithm: Finding the Shortest Paths Between Cities  

## Overview  
This project implements **Dijkstra’s shortest path algorithm** using a **min-heap priority queue** to compute the shortest paths between cities in a directed weighted graph. It reads input from the user, builds a graph using **linked lists**, and applies **Dijkstra’s algorithm** to determine the shortest routes efficiently.

## Features  
- Reads city connections from user input and stores them in a **linked list** (`ArrivalCityList`).  
- Implements a **min-heap priority queue** (`MinPriorityQueue`) for efficient shortest path selection.  
- Uses **Dijkstra’s algorithm** to compute shortest paths dynamically.  
- Allows multiple user queries for different starting cities.  

## Files  
- `Assignment7.cpp` – Main program handling input parsing and shortest path computation.  
- `Graph.h` – Defines the **graph structure** and implements Dijkstra’s algorithm.  
- `ArrivalCityList.h` – Defines a **linked list** structure to store city connections.  
- `MinPriorityQueue.h` – Implements a **min-heap priority queue** for efficient vertex selection.  

## Compilation & Execution  
### **1. Compile the program:**  
```bash
g++ Assignment7.cpp -o Assignment7
