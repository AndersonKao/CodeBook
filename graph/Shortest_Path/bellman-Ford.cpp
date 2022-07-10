// C++ code
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
    void InitializeSingleSource(int Start);     // 以Start作為起點
    void Relax(int X, int Y, int weight);       // 對edge(X,Y)進行Relax
    bool BellmanFord(int Start = 0);            // 以Start作為起點
                                                // if there is negative cycle, return false
};

bool Graph_SP::BellmanFord(int Start){

    InitializeSingleSource(Start);

    for (int i = 0; i < num_vertex-1; i++) {                // |V-1|次的iteration
        // for each edge belonging to E(G)
        for (int j = 0 ; j < num_vertex; j++) {             // 把AdjList最外層的vector走一遍
            for (std::list<std::pair<int,int> >::iterator itr = AdjList[j].begin();
                 itr != AdjList[j].end(); itr++) {          // 各個vector中, 所有edge走一遍
                Relax(j, (*itr).first, (*itr).second);
            }
        }
    }

    // check if there is negative cycle
    for (int i = 0; i < num_vertex; i++) {
        for (std::list<std::pair<int,int> >::iterator itr = AdjList[i].begin();
             itr != AdjList[i].end(); itr++) {
            if (distance[(*itr).first] > distance[i]+(*itr).second) {   // i是from, *itr是to
                return false;
            }
        }
    }

    // print predecessor[] & distance[]
    std::cout << "predecessor[]:\n";
    PrintDataArray(predecessor);
    std::cout << "distance[]:\n";
    PrintDataArray(distance);

    return true;
}
void Graph_SP::PrintDataArray(std::vector<int> array){
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << i;
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++)
        std::cout << std::setw(4) << array[i];
    std::cout << std::endl << std::endl;
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

    Graph_SP g7(6);
    g7.AddEdge(0, 1, 5);
    g7.AddEdge(1, 4, -4);g7.AddEdge(1, 2, 6);
    g7.AddEdge(2, 4, -3);g7.AddEdge(2, 5, -2);
    g7.AddEdge(3, 2, 4);
    g7.AddEdge(4, 3, 1);g7.AddEdge(4, 5, 6);
    g7.AddEdge(5, 0, 3);g7.AddEdge(5, 1, 7);

    if (g7.BellmanFord(0))
        std::cout << "There is no negative cycle.\n";
    else
        std::cout << "There is negative cycle.\n";

    return 0;
}