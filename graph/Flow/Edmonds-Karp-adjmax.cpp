// O((V+E)VE) ，簡單寫成 O(VE²)
#include <cstring>
#include <queue>
using namespace std;
#define maxn 100
typedef int Graph[MAXN][MAXN];  // adjacency matrix
Graph C, F, R;  // 容量上限、流量、剩餘容量
bool visit[MAXN]; // BFS經過的點
int path[MAXN];   // BFS tree
int flow[MAXN];   // 源點到各點的流量瓶頸
 
int BFS(int s, int t)   // 源點與匯點
{
    memset(visit, false, sizeof(visit));
 
    queue<int> Q;   // BFS queue
    visit[s] = true;
    path[s] = s;
    flow[s] = 1e9;
    Q.push(s);
 
    while (!Q.empty())
    {
        int i = Q.front(); Q.pop();
        for (int j=0; j<100; ++j)
            // 剩餘網路找擴充路徑
            if (!visit[j] && R[i][j] > 0)
            {
                visit[j] = true;
                path[j] = i;
                // 一邊找最短路徑，一邊計算流量瓶頸。
                flow[j] = min(flow[i], R[i][j]);
                Q.push(j);
 
                if (j == t) return flow[t];
            }
    }
    return 0;   // 找不到擴充路徑了，流量為零。
}
 
int Edmonds_Karp(int s, int t)
{
    memset(F, 0, sizeof(F));
    memcpy(R, C, sizeof(C));
 
    int f, df;  // 最大流的流量、擴充路徑的流量
    for (f=0; df=BFS(s, t); f+=df)
        // 更新擴充路徑上每一條邊的流量
        for (int i=path[t], j=t; i!=j; i=path[j=i])
        {
            F[i][j] = F[i][j] + df;
            F[j][i] = -F[i][j];
            R[i][j] = C[i][j] - F[i][j];
            R[j][i] = C[j][i] - F[j][i];
        }
    return f;
}