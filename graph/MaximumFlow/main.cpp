#include <iostream>
#include "MaximumFlow.h"

int main() {
    MaximumFlow graph(6, 0, 5);
    graph.addEdge(0, 1, 16);
    graph.addEdge(0, 2,  13);
    graph.addEdge(1, 3, 12);
    graph.addEdge(2, 1, 4);
    graph.addEdge(2, 4, 14);
    graph.addEdge(3, 2, 9);
    graph.addEdge(3, 5, 20);
    graph.addEdge(4, 3, 7);
    graph.addEdge(4, 5, 4);

    graph.print_flow();
    int maxFlow = graph.getMaxFlow();
    std::cout << "The maxFlow is: " << maxFlow << std::endl;
    std::cout << "The result: " << (maxFlow == 23 ? "passed" : "no pass") << std::endl;
    return 0;
}
