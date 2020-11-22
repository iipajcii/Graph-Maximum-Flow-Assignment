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

        int bredth_first_search (int source, int sink) {
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
                // Search all adjacent unvisited nodes v. If the capacity
                // from u to v in the residual network is positive,
                // enqueue v.
            for (v=0; v<nodes; v++) {
                if (visited[v]==0 && capacity[u][v]-flow[u][v]>0) 
                {
                    search_queue.push(v);
                    visited[v] = 1;
                    path[v] = u;
                }
            }
            }
            // If the visited of the sink node is visited now,
            // it means that we reached it.
            return visited[sink] == 2;
        }

        // Ford-Fulkerson Algorithm

        int max_flow () {
            int i,j,u;
            int source = 0;
            int sink = nodes - 1;
            // Initialize empty flow.
            int max_flow = 0;
            for (i=0; i<nodes; i++) {
            for (j=0; j<nodes; j++) {
                flow[i][j] = 0;
            }
            }
            // While there exists an augmenting path,
            // increment the flow along this path.
            while (bredth_first_search(source,sink)) {
                // Determine the amount by which we can increment the flow.
            int increment = INT8_MAX;
            for (u=nodes-1; path[u]>=0; u=path[u]) {
                increment = INT8_MAX < capacity[path[u]][u]-flow[path[u]][u] ? INT8_MAX : capacity[path[u]][u]-flow[path[u]][u];
            }
                // Now increment the flow.
            for (u=nodes-1; path[u]>=0; u=path[u]) {
                flow[path[u]][u] += increment;
                flow[u][path[u]] -= increment;
            }
            max_flow += increment;
            }
            // No augmenting path anymore. We are done.
            cout << "The maximum flow of the graph is: " << max_flow << endl;
            return max_flow;
        }



    public:
        queue <int> search_queue;
        int capacity[100][100];
        int nodes;
        int edges;
        int flow[10][10];     // flow matrix
        int visited[10]; // needed for breadth-first search               
        int path[10];  // array to store augmenting path
};

int main () {
    Graph g;    
    g.max_flow();
    return 0;
}
