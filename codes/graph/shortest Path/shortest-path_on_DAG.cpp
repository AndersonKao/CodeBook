// C++ code
// O(V+E)
#include <iostream>
#include <vector>
#include <list>
#include <utility>          // for std::pair<>
#include <iomanip>          // for std::setw()

const int Max_Distance = 100;
class Graph_SP{             // SP serves as Shortest Path
private:
    int num_vertex;
    std::vector<std::list<std::pair<int,int>>> AdjList;
    std::vector<int> predecessor, distance;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        AdjList.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void PrintDataArray(std::vector<int> array);
    void PrintIntArray(int *array);

    void InitializeSingleSource(int Start);     // 以Start作為起點
    void Relax(int X, int Y, int weight);       // 對edge(X,Y)進行Relax

    void DAG_SP(int Start = 0);                     // 需要 DFS, 加一個額外的Linked list
    void GetTopologicalSort(int *array, int Start);
    void DFSVisit_TS(int *array, int *color, int *discover, 
                     int *finish, int vertex, int &time, int &count);

};
void Graph_SP::GetTopologicalSort(int *array, int Start){

    int color[num_vertex], discover[num_vertex], finish[num_vertex];

    for (int i = 0; i < num_vertex; i++) {
        color[i] = 0;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = -1;
    }

    int time = 0,
        count = num_vertex-1,        // count 為 topologicalsort[] 的 index
        i = Start;

    for (int j = 0; j < num_vertex; j++) {
        if (color[i] == 0) {
            DFSVisit_TS(array, color, discover, finish, i, time, count);
        }
        i = j;
    }
    std::cout << "\nprint discover time:\n";
    PrintIntArray(discover);
    std::cout << "\nprint finish time:\n";
    PrintIntArray(finish);
}
void Graph_SP::DFSVisit_TS(int *array, int *color, int *discover, 
                           int *finish, int vertex, int &time, int &count){

    color[vertex] = 1;  // set gray
    discover[vertex] = ++time;
    for (std::list<std::pair<int,int>>::iterator itr = AdjList[vertex].begin(); 
         itr != AdjList[vertex].end(); itr++) {
        if (color[(*itr).first] == 0) {
            predecessor[(*itr).first] = vertex;
            DFSVisit_TS(array, color, discover, finish, (*itr).first, time, count);
        }
    }
    color[vertex] = 2;  // set black
    finish[vertex] = ++time;
    array[count--] = vertex;            // 產生Topological Sort
}
void Graph_SP::DAG_SP(int Start){

    InitializeSingleSource(Start);      // distance[],predecessor[]的initialization

    int topologicalsort[num_vertex];
    GetTopologicalSort(topologicalsort, Start);

    for (int i = 0; i < num_vertex; i++) {
        int v = topologicalsort[i];
        for (std::list<std::pair<int, int>>::iterator itr = AdjList[v].begin();
             itr != AdjList[v].end(); itr++) {
            Relax(v, (*itr).first, (*itr).second);
        }
    }
    std::cout << "\nprint predecessor:\n";
    PrintDataArray(predecessor);
    std::cout << "\nprint distance:\n";
    PrintDataArray(distance);
}
void Graph_SP::PrintDataArray(std::vector<int> array){
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << i;
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << array[i];
    std::cout << std::endl;
}
void Graph_SP::PrintIntArray(int *array){
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << i;
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << array[i];
    std::cout << std::endl;
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

int main(){

    Graph_SP g8(7);
    g8.AddEdge(0, 1, 3);g8.AddEdge(0, 2, -2);
    g8.AddEdge(1, 3, -4);g8.AddEdge(1, 4, 4);
    g8.AddEdge(2, 4, 5);g8.AddEdge(2, 5, 6);
    g8.AddEdge(3, 5, 8);g8.AddEdge(3, 6, 2);
    g8.AddEdge(4, 3, -3);g8.AddEdge(4, 6, -2);
    g8.AddEdge(5, 6, 2);

    g8.DAG_SP(0);        // 以vertex(0)作為起點

    return 0;
}