#include "Graph.h"
#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include <unordered_map>

void Graph::addNode(int nodeId) {
    if (adjList.find(nodeId) == adjList.end()) {
        adjList[nodeId] = {}; // 初始化节点的邻接列表
        std::cout << "Node " << nodeId << " added to the graph.\n";
    }
}

void Graph::addEdge(int from, int to, double capacity, double weight) {
    Edge forwardEdge = {to, capacity, 0, weight, static_cast<int>(adjList[to].size())};
    Edge reverseEdge = {from, 0, 0, weight, static_cast<int>(adjList[from].size())};
    adjList[from].push_back(forwardEdge);
    adjList[to].push_back(reverseEdge);
}





void Graph::display() const {
    for (const auto &node : adjList) {
        std::cout << "Node " << node.first << ": ";
        for (const auto &edge : node.second) {
            std::cout << "(" << edge.to << ", capacity: " << edge.capacity
                      << ", flow: " << edge.flow
                      << ", weight: " << edge.weight << ") ";
        }
        std::cout << "\n";
    }
}



std::vector<double> Graph::dijkstra(int startNode) {
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;

    std::unordered_map<int, double> distances;
    for (const auto &node : adjList) {
        distances[node.first] = std::numeric_limits<double>::infinity();
    }

    distances[startNode] = 0;
    pq.emplace(0, startNode);

    while (!pq.empty()) {
        auto [currentDistance, currentNode] = pq.top();
        pq.pop();

        if (currentDistance > distances[currentNode]) continue;

        for (const auto &edge : adjList[currentNode]) {
            double newDistance = currentDistance + edge.weight;

            if (newDistance < distances[edge.to]) {
                distances[edge.to] = newDistance;
                pq.emplace(newDistance, edge.to);
            }
        }
    }

    std::vector<double> result;
    for (const auto &node : adjList) {
        result.push_back(distances[node.first]);
    }

    return result;
}

//计算起点到终点的最小流量
double Graph::maxFlow(int source, int sink, double xiaolv) {
    // 默认管道流量（单位：立方米/分钟）
    const double defaultFlowPerMinute = 10000.0;

    // 初始化总流量为默认流量乘以泵站效率
    double totalFlow = defaultFlowPerMinute * xiaolv;

    while (true) {
        std::unordered_map<int, int> parent;
        std::unordered_map<int, int> edgeIndex;
        std::queue<int> q;
        q.push(source);

        while (!q.empty() && parent.find(sink) == parent.end()) {
            int current = q.front();
            q.pop();

            for (size_t i = 0; i < adjList[current].size(); ++i) {
                const Edge &edge = adjList[current][i];
                if (parent.find(edge.to) == parent.end() && edge.to != source && edge.flow < edge.capacity) {
                    parent[edge.to] = current;
                    edgeIndex[edge.to] = i;
                    q.push(edge.to);
                }
            }
        }

        if (parent.find(sink) == parent.end()) break;

        double pathFlow = std::numeric_limits<double>::infinity();
        for (int v = sink; v != source; v = parent[v]) {
            const Edge &edge = adjList[parent[v]][edgeIndex[v]];
            pathFlow = std::min(pathFlow, edge.capacity - edge.flow);
        }

        for (int v = sink; v != source; v = parent[v]) {
            Edge &edge = adjList[parent[v]][edgeIndex[v]];
            edge.flow += pathFlow;
            adjList[edge.to][edge.reverse].flow -= pathFlow;
        }

        totalFlow += pathFlow;
    }

    return totalFlow;
}
