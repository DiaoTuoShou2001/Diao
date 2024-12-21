#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <vector>
#include <limits>
#include <queue>

class Graph {
private:
    struct Edge {
        int to;         // 边的目标节点
        double capacity; // 边的容量
        double flow;     // 当前流量
        double weight;   // 边的权重（用于最短路径计算）
        int reverse;    // 对应反向边在邻接表中的索引
    };

    std::unordered_map<int, std::vector<Edge>> adjList;
public:
    void addNode(int node);
    void addEdge(int from, int to, double weight);
    void display() const;
    double maxFlow(int source, int sink);
    // 迪杰斯特拉算法
    std::vector<double> dijkstra(int startNode);

    void addEdge(int from, int to, double capacity, double weight);

    double maxFlow(int source, int sink, double pumpEfficiency);
};

#endif // GRAPH_H
