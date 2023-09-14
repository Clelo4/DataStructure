//
// Created by jack on 7/9/23.
//

#include <ctime>
#include <cstdlib>
#include <cassert>
#include <vector>
#include "RandomSampling.h"

void RandomSampling::weighted_random_sampling_base(int n, const int *weighted_list, int m, int *result_list) {
    srand(time(nullptr));
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += weighted_list[i];
    }
    int* base_list = new int[total];
    int i = 0;
    int w_idx = 0;
    int weight = weighted_list[w_idx];
    while (i < total) {
        if (weight == 0) {
            w_idx++;
            if (w_idx >= n) break;
            weight = weighted_list[w_idx];
        }
        base_list[i] = w_idx;
        weight--;
        i++;
    }
    assert(i == total);
    for (int j = 0; j < m; ++j) {
        int k = rand() % total;
        result_list[j] = base_list[k];
    }
    delete []base_list;
}

void RandomSampling::weighted_random_sampling(int n, int *weighted_list, int m, int *result_list) {
    int total_weight = 0;
    // 由于使用整数表示权重，所以需要统计所有权重总和
    for (int i = 0; i < n; ++i) total_weight += weighted_list[i];

    srand(time(nullptr));
    for (int i = 0; i < m; ++i) {
        int k = (rand() % total_weight) + 1;

        // 选中
        int prefix_sum = 0;
        int j = -1;
        while (prefix_sum < k) {
            j++;
            while (weighted_list[j] == 0) j++;
            prefix_sum += weighted_list[j];
        }
        total_weight -= weighted_list[j];
        result_list[i] = j;
        weighted_list[j] = 0;
    }
}

void RandomSampling::reservoir_sampling(int m, int *result_list, const int *flow_list, int n) {
    srand(time(nullptr));

    int i = 0;
    for (; i < m; ++i) {
        // 在每次循环中，i被保留下来的概率是100%
        result_list[i] = flow_list[i];
    }

    for (; i < n; ++i) {
        // 在每次循环中，第i个元素和蓄水池的元素被保留下来的概率都是k/i

        int k = rand() % i;
        if (k < m) {
            result_list[k] = flow_list[i];
        }

        // 分析：
        // 对于新加入的元素i：被保留的概率是k/i，被丢弃的概率是(i-m)/i
        // 对于蓄水池的元素，被保留的概率是k/(i-1) * ((i-m)/i + m/i * ((m - 1)/m)) =
        // m/(i-1) * ((i-m)/i + (m-1)/i) =
        // m/(i-1) * (i-1)/i =
        // m/i
    }
}

class Node {
public:
    Node* left_child;
    Node* right_child;
    int left;
    int right;
    int index;
    Node(int index, int left, int right): left(left), right(right), left_child(nullptr), right_child(nullptr), index(index) {}
};

Node* build(std::vector<Node*> list, int left, int right) {
    if (left == right) return nullptr;
    if (left == right - 1) return list[left];
    int mid = (left + right) / 2;
    Node* parent = list[mid];
    parent->left_child = build(list, left, mid);
    parent->right_child = build(list, mid + 1, right);
    return parent;
}

Node* search(Node* root, int search_key) {
    if (root == nullptr) return root;
    if (root->left > search_key) return search(root->left_child, search_key);
    else if (root->right <= search_key) return search(root->right_child, search_key);
    return root;
}

void RandomSampling::weighted_random_sampling_bst(int n, const int *weighted_list, int m, int *result_list) {
    int total = 0;
    for (int i = 0; i < n; ++i) {
        total = weighted_list[i];
    }

    int pre_sum = 0;
    std::vector<Node*> node_list;
    for (int i = 0; i < n; ++i) {
        int weight = weighted_list[i];
        Node* cur = new Node(i, pre_sum, pre_sum + weight);
        pre_sum += weight;
        node_list.push_back(cur);
    }
    int total_weight = pre_sum;

    Node* root = build(node_list, 0, static_cast<int>(node_list.size()));

    srand(time(nullptr) + 1);
    for (int i = 0; i < m; ++i) {
        int rand_weight = rand() % total_weight;
        result_list[i] = search(root, rand_weight)->index;
    }
}
