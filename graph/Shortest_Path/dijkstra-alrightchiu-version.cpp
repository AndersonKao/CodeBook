// C++ code
#include <iostream>
#include <vector>
#include <list>
#include <utility>          // for std::pair<>
#include <iomanip>          // for std::setw()
#include <cmath>            // for std::floor
// #include "Priority_Queue_BinaryHeap.h"

const int Max_Distance = 100;
class Graph_SP{             // SP serves as Shortest Path
private:
    int num_vertex;
    std::vector<std::list<std::pair<int,int>>> AdjList;
    std::vector<int> predecessor, distance;
    std::vector<bool> visited;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        AdjList.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void PrintDataArray(std::vector<int> array);
    void PrintIntArray(int *array);

    void InitializeSingleSource(int Start);     // 以Start作為起點
    void Relax(int X, int Y, int weight);       // edge方向：from X to Y

    void Dijkstra(int Start = 0);        // 需要Min-Priority Queue
    friend class BinaryHeap;             // 以Binary Heap實現Min-Priority Queue
};
void Graph_SP::Dijkstra(int Start){

    InitializeSingleSource(Start);

    BinaryHeap minQueue(num_vertex);   // object of min queue
    minQueue.BuildMinHeap(distance);

    visited.resize(num_vertex, false);   // initializa visited[] as {0,0,0,...,0}

    while (!minQueue.IsHeapEmpty()) {
        int u = minQueue.ExtractMin();
        for (std::list<std::pair<int, int>>::iterator itr = AdjList[u].begin();
             itr != AdjList[u].end(); itr++) {

            Relax(u, (*itr).first, (*itr).second);
            minQueue.DecreaseKey((*itr).first, distance[(*itr).first]); // definition at alrightchiu's priority queue self-version
        }
    }
    std::cout << "\nprint predecessor:\n";
    PrintDataArray(predecessor);
    std::cout << "\nprint distance:\n";
    PrintDataArray(distance);
}
void Graph_SP::InitializeSingleSource(int Start){

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        distance[i] = Max_Distance;
        predecessor[i] = -1;
    }
    distance[Start] = 0;
}
void Graph_SP::Relax(int from, int to, int weight){

    if (distance[to] > distance[from] + weight) {
        distance[to] = distance[from] + weight;
        predecessor[to] = from;
    }
}
void Graph_SP::AddEdge(int from, int to, int weight){

    AdjList[from].push_back(std::make_pair(to,weight));
}
void Graph_SP::PrintDataArray(std::vector<int> array){
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << i;
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << array[i];
    std::cout << std::endl;
}
int main(){

    Graph_SP g9(6);
    g9.AddEdge(0, 1, 8);g9.AddEdge(0, 5, 1);
    g9.AddEdge(1, 0, 3);g9.AddEdge(1, 2, 1);
    g9.AddEdge(2, 0, 5);g9.AddEdge(2, 3, 2);g9.AddEdge(2, 4, 2);
    g9.AddEdge(3, 1, 4);g9.AddEdge(3, 2, 6);g9.AddEdge(3, 4, 7);g9.AddEdge(3, 5, 3);
    g9.AddEdge(5, 3, 2);g9.AddEdge(5, 4, 8);

    g9.Dijkstra(0);

    return 0;
}