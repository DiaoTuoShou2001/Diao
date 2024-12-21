#ifndef JIANMO_H
#define JIANMO_H

class Graph;
class PipeManager;

#include "Graph.h"
#include "PipeManager.h"

namespace jianmo {
    void buildGraphFromData(Graph& graph, PipeManager& pipeManager);
}


#endif // JIANMO_H
