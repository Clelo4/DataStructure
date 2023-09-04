//
// Created by chengjunjie on 2023/8/22.
//

#include <cassert>
#include <cstring>
#include <iostream>
#include <queue>
#include "MaximumFlow.h"

int min(int a, int b) {
    if (a <= b) return a;
    else return b;
}

MaximumFlow::MaximumFlow(int vertex, int source, int end):vertex(vertex), source(source), end(end) {
    assert(source >= 0);
    assert(source < vertex);
    assert(end < vertex);

    // 初始化流网络
    flow_matrix = new int*[vertex];
    memset(flow_matrix, 0, sizeof(int *) * vertex);
    for (int i = 0; i < vertex; ++i) {
        *(flow_matrix + i) = new int[vertex];
        memset(*(flow_matrix + i), 0, sizeof(int) * vertex);
    }

    // 初始化容量矩阵
    capacity_matrix = new int*[vertex];
    memset(capacity_matrix, 0, sizeof(int*) *vertex);
    for (int i = 0; i < vertex; ++i) {
        capacity_matrix[i] = new int[vertex];
        memset(*(capacity_matrix + i), 0, sizeof(int) * vertex);
    }

    // 初始化邻接表
    for (int i = 0; i < vertex; ++i) {
        adjacency_list.emplace_back();
    }

    // 初始化前驱结点映射表
    precursor_vertex = new int[vertex];
    memset(precursor_vertex, 0, sizeof(int) * vertex);
}

bool MaximumFlow::bfs() {
    // 在残存网络执行广度优先的最短路径算法，每条边的权重为单位距离
    // 当残存网络上边的残存容量为0，说明此边不通

    memset(precursor_vertex, 0, sizeof(int) * vertex);

    bool visited[this->vertex];
    memset(visited, 0, sizeof(visited));

    std::queue<int> toDo;
    toDo.push(this->source);
    visited[this->source] = true;
    bool is_arrive_end = false;

    while (!toDo.empty()) {
        int from = toDo.front();
        toDo.pop();

        // 到达汇点
        if (from == this->end) {
            is_arrive_end = true;
            break;
        }

        // 遍历相邻结点
        for (int to : adjacency_list[from]) {
            // 已经访问过
            if (visited[to]) continue;

            int edge_flow = flow_matrix[from][to];

            int save_capacity = 0;

            if (capacity_matrix[from][to] > 0) {
                // from->to是正向边
                save_capacity = capacity_matrix[from][to] - edge_flow;
            } else {
                // from->to是反向边
                save_capacity = flow_matrix[to][from] - edge_flow;
            }
            if (save_capacity > 0) {
                visited[to] = true;
                toDo.push(to);
                precursor_vertex[to] = from;
            }
        }
    }

    return is_arrive_end;
}

int MaximumFlow::edmondsKarp() {
    // 初始化flow_grash，由于之前已经初始化，这一步无需任何操作

    while (bfs()) {
        int cur = this->end;
        int min_path_flow = INT_MAX;
        while (true) {
            int pre = precursor_vertex[cur];
            int from = pre, to = cur;

            if (capacity_matrix[from][to] > 0) {
                // from->to是正向边
                min_path_flow = min(min_path_flow, capacity_matrix[from][to] - flow_matrix[from][to]);
            } else {
                // from->to是反向边
                min_path_flow = min(min_path_flow, flow_matrix[to][from] - flow_matrix[from][to]);
            }
            if (pre == this->source) {
                break;
            }
            cur = pre;
        }

        cur = this->end;
        while(true) {
            int pre = precursor_vertex[cur];
            int from = pre, to = cur;

            if (capacity_matrix[from][to] > 0) {
                // from->to是正向边
                flow_matrix[from][to] += min_path_flow;
            } else {
                flow_matrix[to][from] -= min_path_flow;
            }

            if (pre == this->source) {
                break;
            }
            cur = pre;
        }
    }

    int res = 0;
    for (int to : adjacency_list[this->source]) {
        res += flow_matrix[this->source][to] - flow_matrix[to][this->source];
    }
    return res;
}

int MaximumFlow::getMaxFlow() {
    return edmondsKarp();
}

bool MaximumFlow::addEdge(int from, int to, int capacity) {
    assert(from < vertex);
    assert(to < vertex);
    assert(from != to);
    assert(capacity > 0);
    // 构建流网络的邻接矩阵
    adjacency_list[from].push_back(to);
    adjacency_list[to].push_back(from);
    // 添加容量
    (*(capacity_matrix + from))[to] = capacity;
    (*(capacity_matrix + to))[from] = 0;
    return false;
}

MaximumFlow::~MaximumFlow() {
    for (int i = 0; i < vertex; i++) {
        delete capacity_matrix[i];
        delete flow_matrix[i];
    }
    delete flow_matrix;
    delete capacity_matrix;
    delete precursor_vertex;
}

void MaximumFlow::print_flow() {
    for (int from = 0; from < vertex; ++from) {
        auto& adjacency = adjacency_list[from];
        for (int to : adjacency) {
            std::cout << from << " -> " << to << ": " << capacity_matrix[from][to] << std::endl;
        }
    }
}

