// C++ code
// by alrightchiu
// all pairs shortest path
#include <iostream>
#include <vector>
#include <iomanip>      // for setw()

const int MaxDistance = 1000;
class Graph_SP_AllPairs{
private:
    int num_vertex;
    std::vector< std::vector<int> > AdjMatrix, Distance, Predecessor;
public:
    Graph_SP_AllPairs():num_vertex(0){};
    Graph_SP_AllPairs(int n);
    void AddEdge(int from, int to, int weight);
    void PrintData(std::vector< std::vector<int> > array);
    void InitializeData();
    void FloydWarshall();
};

Graph_SP_AllPairs::Graph_SP_AllPairs(int n):num_vertex(n){
    // Constructor, initialize AdjMatrix with 0 or MaxDistance
    AdjMatrix.resize(num_vertex);
    for (int i = 0; i < num_vertex; i++) {
        AdjMatrix[i].resize(num_vertex, MaxDistance);
        for (int j = 0; j < num_vertex; j++) {
            if (i == j){
                AdjMatrix[i][j] = 0;
            }
        }
    }
}
void Graph_SP_AllPairs::InitializeData(){
    Distance.resize(num_vertex);
    Predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
        Distance[i].resize(num_vertex);
        Predecessor[i].resize(num_vertex, -1);
        for (int j = 0; j < num_vertex; j++) {
            Distance[i][j] = AdjMatrix[i][j];
            if (Distance[i][j] != 0 && Distance[i][j] != MaxDistance) {
                Predecessor[i][j] = i;
            }
        }
    }
}
void Graph_SP_AllPairs::FloydWarshall(){

    InitializeData();

    std::cout << "initial Distance[]:\n";
    PrintData(Distance);
    std::cout << "\ninitial Predecessor[]:\n";
    PrintData(Predecessor);

    for (int k = 0; k < num_vertex; k++) {
        std::cout << "\nincluding vertex(" << k << "):\n";
        for (int i = 0; i < num_vertex; i++) {
            for (int j = 0; j < num_vertex; j++) {
                if ((Distance[i][j] > Distance[i][k]+Distance[k][j]) 
                     && (Distance[i][k] != MaxDistance)) {
                    Distance[i][j] = Distance[i][k]+Distance[k][j];
                    Predecessor[i][j] = Predecessor[k][j];
                }
            }
        }
        // print data after including new vertex and updating the shortest paths
        std::cout << "Distance[]:\n";
        PrintData(Distance);
        std::cout << "\nPredecessor[]:\n";
        PrintData(Predecessor);
    }
}
void Graph_SP_AllPairs::PrintData(std::vector< std::vector<int> > array){

    for (int i = 0; i < num_vertex; i++){
        for (int j = 0; j < num_vertex; j++) {
            std::cout << std::setw(5) << array[i][j];
        }
        std::cout << std::endl;
    }
}
void Graph_SP_AllPairs::AddEdge(int from, int to, int weight){
    AdjMatrix[from][to] = weight;
}

int main(){

    Graph_SP_AllPairs g10(4);
    g10.AddEdge(0, 1, 2);g10.AddEdge(0, 2, 6);g10.AddEdge(0, 3, 8);
    g10.AddEdge(1, 2, -2);g10.AddEdge(1, 3, 3);
    g10.AddEdge(2, 0, 4);g10.AddEdge(2, 3, 1);

    g10.FloydWarshall();

    return 0;
}
