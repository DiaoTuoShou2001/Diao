#include <iostream>
#include "jianmo.h"
namespace jianmo {
    void buildGraphFromData(Graph &gasNetwork, PipeManager &manager) {
        // 添加泵站作为图的节点
        for (const auto &station : manager.getStations()) {
            gasNetwork.addNode(station.getId());
        }

        // 添加管道作为图的边
        for (const auto &pipe : manager.getPipes()) {
            if (pipe.getStartStationId() != -1 && pipe.getEndStationId() != -1) {
                gasNetwork.addEdge(pipe.getStartStationId(), pipe.getEndStationId(), pipe.getLength(), pipe.getLength());
            } else {
                std::cerr << "Warning: Pipeline " << pipe.getName()
                          << " does not have valid start or end stations.\n";
            }
        }

        std::cout << "Gas network graph built successfully.\n";
    }
}
