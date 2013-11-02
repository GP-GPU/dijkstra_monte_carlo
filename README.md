dijkstra_monte_carlo
====================

A Monte Carlo simulation to find the average shortest paths in random graphs using Dijkstra's shortest path algorithm 

- This program uses the edge-list representation for representing the graph, because real world graphs are usually sparse and are hence more efficiently represented using an edge-list representation. However, under this representation, instead of actually using a linked list to keep track of the vertices connected to a given vertex, I use a vector. This is because for this particular problem, for a given random graph, the vertices and their connections do not change. Hence using a linked list here would not have provided any actual value. On the contrary, the performance of the program increases greatly as vectors provide access to any connected vertex in constant time.

- I first tried using 'std::priority_queue' for the open set, but then realised that it isn't suitable for two reasons:
    1. there is no 'contains' method to check whether the vertex under consideration is already in the open set or not
    2. there is no way to update the value of an element in the priority queue (this is needed in cases where a path shorter than one discovered earlier is found during algorithm execution, which requires that the open set be appropriately updated).
Both these operations (checking whether a vertex is already present in the open set and updating it's shortest path to the source vertex) require traversing through the open set vertices (linear time). Hence to minimise the performance penalty, I have combined these traversals into a single function called 'updateIfExistsElseAdd'.

- I also templated the priority queue class in order to make it generic, but the function 'updateIfExistsElseAdd' is very specific to this problem at hand. So actually using this function somewhat defeats the purpose of templating the priority queue class.

- The file 'main.hpp' contain variables that control parameters of the program, so configuring the program is currently restricted to compile-time. This behaviour can be enhanced either by:
    - passing command-line arguments
    - using a separate configuration file
    - providing a menu of operations
    - making a GUI

- In the 'main.cpp' file, in the main function, there is a "#if 1 ... #else ... #endif" block. The "#if 1" block executes the program as decribed in the problem calculating the average shortest path from a source vertex to all other vertices. On the other hand, the "#else" block (which can be enabled by changing '#if 1' to '#if 0') can be used to check whether Dijkstra's algorithm as implemented in this program works correctly or not. This "#else" block prints the edge-list representation of a single graph, and allows the user to choose a source vertex and a destination vertex. Then it applies Dijkstra's shortest path algorithm and prints the shortest path from the source to the destination along with the cost.

- Boost.Random from the Boost C++ libraries has been used as the random number generator. This means that you would need to have Boost installed on your system to build and run this program.
If you are new to Boost, start here: http://www.boost.org/doc/libs/1_54_0/more/getting_started/index.html
Boost.Random is here: http://www.boost.org/doc/libs/1_54_0/doc/html/boost_random.html
Note also that the same seed is used every time the program runs. So for one program execution, a random set of graphs are generated. But if the program is run again, the same set of random graphs will be produced. This was useful for debugging, but would need to be enhanced for a real-world application.


Build instructions:
-------------------
    get all the cpp and hpp files into one directory
    g++ *.cpp -I/path/to/boost/boost_1_54_0 -o dijkstra
    ./dijkstra


Execution metrics:
------------------
    (with number of vertices per graph = 50, no self loops, edge density = 0.4, min edge cost = 1.0, max edge cost = 10.0) 
        number of graphs    execution time (in seconds)    avg of avg shortest paths in all graphs
        ----------------    ---------------------------    ---------------------------------------
                1                      0.031                              3.408
               10                      0.238                              3.826
              100                      2.381                              3.783
             1000                     24.184                              3.899
            10000                    240.178                              3.899
