#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

struct Edge {
    int u, v, weight;
};

class Graph {
private:
    int V, E;
    vector<Edge> edges;
    vector<vector<int>> adjacencyMatrix;

public:
    Graph(int vertices, int edges) {
        V = vertices;
        E = edges;
        adjacencyMatrix.resize(V, vector<int>(E, 0));
    }

    void addEdge(int u, int v, int weight, int edgeIndex) {
        if (u == v) {
            adjacencyMatrix[u - 1][edgeIndex] = 2;
        } else {
            adjacencyMatrix[u - 1][edgeIndex] = 1;
            adjacencyMatrix[v - 1][edgeIndex] = -1;
        }
        edges.push_back({u, v, weight});
    }

    void printIncidenceMatrix() {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < E; j++) {
                int n = adjacencyMatrix[i][j];
                if (n >= 0) {
                    cout << " ";
                }
                cout << n << " ";
            }
            cout << endl;
        }
    }

    vector<int> dijkstra(int startVertex) {
        vector<int> distance(V, INT_MAX);
        vector<bool> visited(V, false);

        distance[startVertex - 1] = 0;

        for (int i = 0; i < V - 1; i++) {
            int minDistance = INT_MAX;
            int minVertex = -1;

            for (int v = 0; v < V; v++) {
                if (!visited[v] && distance[v] < minDistance) {
                    minDistance = distance[v];
                    minVertex = v;
                }
            }

            if (minVertex == -1) continue;

            visited[minVertex] = true;

            for (int j = 0; j < E; j++) {
                if (adjacencyMatrix[minVertex][j] == 1) {
                    int neighbor = 0;
                    for (int k = 0; k < V; k++) {
                        if (adjacencyMatrix[k][j] == -1) {
                            neighbor = k;
                            break;
                        }
                    }
                    if (!visited[neighbor] && distance[minVertex] != INT_MAX
                        && distance[minVertex] + edges[j].weight < distance[neighbor]) {
                        distance[neighbor] = distance[minVertex] + edges[j].weight;
                    }
                }
            }
        }
        return distance;
    }
};

/*
Входные данные для графа в варианте:
10
16
1 4 2
1 3 4
1 2 3
2 6 3
3 6 6
4 6 2
4 5 5
5 7 6
5 9 12
6 5 1
6 7 8
6 8 7
7 10 4
8 10 3
9 8 6
9 10 11
*/

int main() {
    SetConsoleOutputCP(CP_UTF8);
    /*int V, E;
    cout << "Введите кол-во вершин:";
    cin >> V;
    cout << "Введите кол-во ребер:";
    cin >> E;

    Graph graph(V, E);
    cout << "Введите ребра (u v weight):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph.addEdge(u, v, weight, i);
    }
    */

    int V = 10;
    int E = 16;

    Graph graph(V, E);

    graph.addEdge(1, 4, 2, 0);
    graph.addEdge(1, 3, 4, 1);
    graph.addEdge(1, 2, 3, 2);
    graph.addEdge(2, 6, 3, 3);
    graph.addEdge(3, 6, 6, 4);
    graph.addEdge(4, 6, 2, 5);
    graph.addEdge(4, 5, 5, 6);
    graph.addEdge(5, 7, 6, 7);
    graph.addEdge(5, 9, 12, 8);
    graph.addEdge(6, 5, 1, 9);
    graph.addEdge(6, 7, 8, 10);
    graph.addEdge(6, 8, 7, 11);
    graph.addEdge(7, 10, 4, 12);
    graph.addEdge(8, 10, 3, 13);
    graph.addEdge(9, 8, 6, 14);
    graph.addEdge(9, 10, 11, 15);

    cout << "Матрица инцидентности:" << endl;
    graph.printIncidenceMatrix();
    cout << endl;

    int startVertex;
    cout << "Введите вершину, пути из которой вы хотите найти:";
    cin >> startVertex;
    cout << endl;

    vector<int> shortestPath = graph.dijkstra(startVertex);

    cout << "Самые котроткие расстояния до каждой вершин из вершины " << startVertex << ":\n";
    for (int i = 0; i < V; ++i) {
        cout << "Вершина " << (i + 1) << ": ";
        if (shortestPath[i] != INT_MAX)
            cout << shortestPath[i];
        else
            cout << "Нет пути!";
        cout << endl;
    }

    return 0;
}
