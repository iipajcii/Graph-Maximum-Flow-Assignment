#include <iostream>
#include <queue>
#include <limits>
#include <fstream>
using namespace std;

class Graph {
    public:
        Graph() {
            // Initializing Graph and opening Graph.txt
            int x,y,value;
            ifstream graph_file("Graph.txt");
            graph_file >> nodes;
            graph_file >> edges;

            // Zeroing the values of the Graph Edges
            for (int counter=0; counter<nodes; counter++)
            for (int counter2=0; counter2<nodes; counter2++) 
            {
                capacity[counter][counter2] = 0;
            }

            // Reading values for Graph Weights
            while(!graph_file.eof()) {
                graph_file >> x;
                graph_file >> y;
                graph_file >> value;
                capacity[x][y] = value;
            }
            graph_file.close();
        }

        bool breadth_first_search (int source, int sink) {
            int u,v;
            // Initializing All Nodes to unvisited
            for (u=0; u<nodes; u++) {
                visited[u] = 0;
            }
            
            search_queue.push(source);
            visited[source] = 1;

            path[source] = -1;
            while (!search_queue.empty()) {
            u = search_queue.front();
            visited[u] = 2;
            search_queue.pop();
            
            //Enqueue all the nodes that can still allow resources to residual
            for (v=0; v<nodes; v++) {
                if (visited[v]==0 && capacity[u][v]-residual[u][v]>0) 
                {
                    search_queue.push(v);
                    visited[v] = 1;
                    path[v] = u;
                }
            }
            }
            //If the sink node has been visited then the breadth-first-search
            //has found a path that can still take resources
            return (visited[sink] == 2);
        }

        // Ford-Fulkerson Algorithm

        int max_residual () {
            
            int source = 0;
            int sink = nodes - 1;
            // Initialize empty residual.
            int max_residual = 0;
            for (int counter1 = 0; counter1 < nodes; counter1++) {
                for (int counter2 = 0; counter2 < nodes; counter2++) {
                    residual[counter1][counter2] = 0;
                }
            }

            //While the Breadth_First_Search finds a path that can handle resource, send the resources
            while (breadth_first_search(source,sink)) {

            //Determine the maximum amount of resource that can be transfered
            int increment = INT8_MAX;
            for (int counter = nodes-1; path[counter] >= 0; counter = path[counter]) {
                increment = INT8_MAX < capacity[path[counter]][counter]-residual[path[counter]][counter] ? INT8_MAX : capacity[path[counter]][counter]-residual[path[counter]][counter];
            }
            
            //Transfer maximum resources down the augmented path  and updated the residual graph
            for (int counter = nodes-1; path[counter]>=0; counter = path[counter]) {
                residual[path[counter]][counter] += increment;
                residual[counter][path[counter]] -= increment;
            }
            max_residual += increment;
            }
            // At the end of the while loop there are no more residual graphs
            cout << "The maximum residual of the graph is: " << max_residual << endl;
            return max_residual;
        }

    public:
        queue <int> search_queue;//The Queue used with the Breadth First Search
        int nodes;               //The Number of Nodes of the Graph
        int edges;               //The Number of Edges of the Graph
        int capacity[100][100];  //The Capacity of the Graph
        int residual[100][100];  //Represents the residual flow of the graph 
        int visited[100];        //Stores the status of nodes that have been visited during breadth-first-traversal
        int path[100];           //Stores the Augmented Path
};

int main () {
    Graph g;    
    g.max_residual();
    return 0;
}
