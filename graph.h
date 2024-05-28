#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include "binread.cpp"

using namespace std;

const int MAX_VERTICES = 1000; // Adjust this value according to your needs

struct Edge
{
    int destination;
    int weight;
};

class Graph
{
private:
    vector<vector<Edge>> adjacencyList;
    int numVertices;

public:
    Graph() {}
    Graph(int vertices) : numVertices(vertices)
    {
        adjacencyList.resize(numVertices);
    }

    void addEdge(int source, int destination, int weight)
    {
        adjacencyList[source].push_back({destination, weight});
        adjacencyList[destination].push_back({source, weight});
    }

    int dijkstraMiniTime(int source, int destination) {
    vector<int> distances(numVertices, INT_MAX);
    vector<bool> visited(numVertices, false);
    vector<int> previous(numVertices, -1);

    distances[source] = 0;

    for (int i = 0; i < numVertices - 1; ++i) {
        int minDistance = INT_MAX;
        int minIndex = -1;

        for (int j = 0; j < numVertices; ++j) {
            if (!visited[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                minIndex = j;
            }
        }

        if (minIndex == -1) {
            break;
        }

        visited[minIndex] = true;

        for (const auto& edge : adjacencyList[minIndex]) {
            int neighbor = edge.destination;
            int weight = edge.weight;

            if (!visited[neighbor] && distances[minIndex] + weight < distances[neighbor]) {
                distances[neighbor] = distances[minIndex] + weight;
                previous[neighbor] = minIndex; // Update previous vertex
            }
        }
    }

    if (distances[destination] == INT_MAX) {
        return -1; // No valid path from source to destination
    } else {
        // Construct the shortest path
        vector<int> shortestPath;
        int current = destination;
        while (current != -1) {
            shortestPath.push_back(current);
            current = previous[current];
        }

        // Print the shortest path
        cout << "Shortest path from source to destination: ";
        for (int i = shortestPath.size() - 1; i >= 0; --i) {
            cout << shortestPath[i];
            if (i > 0) {
                cout << " -> ";
            }
        }
        cout << endl;

        return distances[destination];
    }
}
};

Graph graphmaker()
{
    int numLocations = 10000;
    Graph graph(numLocations);
    graph.addEdge(1001, 0, 15); 
    graph.addEdge(0, 1, 4); // according to the bin_data.csv file
    graph.addEdge(1, 2, 1);
    graph.addEdge(2, 3, 2);
    graph.addEdge(3, 4, 2);
    graph.addEdge(4, 5, 3);
    graph.addEdge(5, 6, 5);
    graph.addEdge(6, 7, 1);
    graph.addEdge(7, 8, 5);
    graph.addEdge(8, 9, 2);
    graph.addEdge(9, 0, 5);
    graph.addEdge(9, 101, 3);
    graph.addEdge(101, 10, 1);
    graph.addEdge(1002, 10, 15);
    graph.addEdge(10, 11, 3);
    graph.addEdge(11, 12, 1);
    graph.addEdge(12, 13, 4);
    graph.addEdge(13, 14, 4);
    graph.addEdge(14, 15, 5);
    graph.addEdge(15, 16, 5);
    graph.addEdge(16, 17, 4);
    graph.addEdge(17, 18, 1);
    graph.addEdge(18, 19, 4);
    graph.addEdge(19, 10, 2);
    graph.addEdge(102, 20, 5);
    graph.addEdge(1003, 20, 15);
    graph.addEdge(20, 21, 3);
    graph.addEdge(21, 22, 5);
    graph.addEdge(22, 23, 5);
    graph.addEdge(23, 24, 3);
    graph.addEdge(24, 25, 3);
    graph.addEdge(25, 26, 2);
    graph.addEdge(26, 27, 2);
    graph.addEdge(27, 28, 5);
    graph.addEdge(28, 29, 1);
    graph.addEdge(29, 20, 3);
    graph.addEdge(103, 29, 5);
    graph.addEdge(103, 30, 5);
    graph.addEdge(1004, 30, 15);
    graph.addEdge(30, 31, 5);
    graph.addEdge(31, 32, 5);
    graph.addEdge(32, 33, 1);
    graph.addEdge(33, 34, 2);
    graph.addEdge(34, 35, 4);
    graph.addEdge(35, 36, 3);
    graph.addEdge(36, 37, 3);
    graph.addEdge(37, 38, 1);
    graph.addEdge(38, 39, 3);
    graph.addEdge(39, 30, 2);
    graph.addEdge(104, 39, 5);
    graph.addEdge(104, 40, 5);
    graph.addEdge(1005, 40, 15);
    graph.addEdge(40, 41, 5);
    graph.addEdge(41, 42, 2);
    graph.addEdge(42, 43, 4);
    graph.addEdge(43, 44, 5);
    graph.addEdge(44, 45, 1);
    graph.addEdge(45, 46, 5);
    graph.addEdge(46, 47, 4);
    graph.addEdge(47, 48, 2);
    graph.addEdge(48, 49, 2);
    graph.addEdge(49, 40, 1);
    graph.addEdge(105, 49, 3);
    return graph;
}

/*int main() {

/* int one, two;
    cout << "Enter two locations: "<<endl;
    cout<<"1: ";
    cin >> one;
    cout<<"2: ";
    cin >> two;
    cout << endl;

    int shortestPath = graph.dijkstraMiniTime(one, two); // Replace 0 and 5 with the desired source and destination vertices

    if (shortestPath == -1)
    {
        cout << "No valid path from source to destination." << endl;
    }
    else
    {
        cout << "Minimum Travel Time from source to destination: " << shortestPath <<"Minutes"<< endl;
    }*/
