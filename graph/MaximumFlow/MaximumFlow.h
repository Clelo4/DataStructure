//
// Created by chengjunjie on 2023/8/22.
//

#ifndef MAXIMUM_FLOW_H
#define MAXIMUM_FLOW_H

#include <vector>

class MaximumFlow {
public:
    explicit MaximumFlow(int vertex, int source, int end);
    ~MaximumFlow();

    /**
     * 获取最大流
     * @return 返回最大流值
     */
    int getMaxFlow();
    /**
     * 添加一条边
     * @param from 起点
     * @param to 终点
     * @param capacity 边的容量
     * @return 是否添加成功
     */
    bool addEdge(int from, int to, int capacity);

    void print_flow();

private:
    // 结点数
    int vertex = 0;
    // 源结点
    int source;
    // 汇结点
    int end;

    /**
     * 使用广度优先算法在残存网络中查找最短距离的增广路径
     * @return 是否存在最短距离的增广路径
     */
    bool bfs();

    // 使用Edmonds Karp算法查找最大流
    int edmondsKarp();

    // 残存流网络
    int** flow_matrix = nullptr;

    // 原始流网络容量矩阵
    int** capacity_matrix = nullptr;

    // 邻接矩阵
    std::vector<std::vector<int>> adjacency_list;

    // 前向结点
    int* precursor_vertex;
};

#endif //MAXIMUM_FLOW_H
