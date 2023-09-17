//
// Created by jack on 7/9/23.
//

#include <ctime>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <stack>
#include "RandomSampling.h"

time_t RandomSampling::seed = time(nullptr);

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

void RandomSampling::weighted_random_sampling_binary_search(int n, const int *weighted_list, int m, int *result_list) {
    int total_weight = 0;
    std::vector<int> pre_sum_list;
    pre_sum_list.push_back(0);
    for (int i = 0; i < n; ++i) {
        total_weight += weighted_list[i];
        pre_sum_list.push_back(total_weight);
    }

    srand(time(nullptr));
    for (int i = 0; i < m; ++i) {
        int k = rand() % total_weight;

        int left = 0, right = static_cast<int>(pre_sum_list.size()) - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (pre_sum_list[mid] == k) {
                left = mid;
                break;
            }
            else if (pre_sum_list[mid] < k) {
                if (mid == pre_sum_list.size() - 2 || pre_sum_list[mid + 1] >= k) {
                    left = mid;
                    break;
                }
                if (pre_sum_list[mid + 1] < k) {
                    left = mid + 1;
                }
            }
            else {
                right = mid - 1;
            }
        }

        result_list[i] = left;
    }
}

class NodeTwo {
public:
    NodeTwo* left;
    NodeTwo* right;
    int total;
    bool is_leaf;
    int index = -1;
    explicit NodeTwo(NodeTwo* left = nullptr, NodeTwo* right = nullptr, int total = 0, int is_leaf = false) : left(left), right(right), total(total), is_leaf(is_leaf) {}
};

NodeTwo* build_two(std::vector<NodeTwo*> list, int left, int right) {
    if (left == right) return nullptr;
    if (left == right - 1) return list[left];
    int mid = (left + right) / 2;
    NodeTwo* left_child = build_two(list, left, mid);
    NodeTwo* right_child = build_two(list, mid, right);
    if (left_child != nullptr && right_child != nullptr) {
        auto* parent = new NodeTwo(left_child, right_child, left_child->total + right_child->total);
        return parent;
    }
    if (left_child == nullptr) return right_child;
    return left_child;
}

NodeTwo* search_and_delete(NodeTwo* root, int k, int* res) {
    if (root == nullptr) return nullptr;
    if (root->is_leaf) {
        *res = root->index;
        delete root;
        return nullptr;
    }
    if (k < root->left->total) {
        auto* ret = search_and_delete(root->left, k, res);
        if (ret == nullptr) {
            auto* new_root = root->right;
            delete root;
            return new_root;
        } else {
            root->left = ret;
            root->total = root->left->total + root->right->total;
            return root;
        }
    } else {
        auto* ret = search_and_delete(root->right, k - root->left->total, res);
        if (ret == nullptr) {
            auto* new_root = root->left;
            delete root;
            return new_root;
        } else {
            root->right = ret;
            root->total = root->left->total + root->right->total;
            return root;
        }
    }
    exit(-1);
}

void
RandomSampling::weighted_random_sampling_bst_no_put_back(int n, const int *weighted_list, int m, int *result_list) {
    std::vector<NodeTwo*> node_list;
    int total_weight = 0;
    for (int i = 0; i < n; ++i) {
        int weight = weighted_list[i];
        total_weight += weight;
        auto* cur = new NodeTwo(nullptr, nullptr, weight, true);
        cur->index = i;
        node_list.push_back(cur);
    }

    NodeTwo* root = build_two(node_list, 0, static_cast<int>(node_list.size()));

    srand(time(nullptr) + 1);
    for (int i = 0; i < m; ++i) {
        int rand_weight = rand() % total_weight;
        int res;
        root = search_and_delete(root, rand_weight, &res);
        result_list[i] = res;
        total_weight -= weighted_list[res];
    }
}

void RandomSampling::weighted_random_sample_alias_method_navie(int n, const double *weighted_list, int m, int *result_list) {
    auto* alias_table = new int[n];
    auto* prob_table = new double[n];

    struct Node {
        double probability;
        Node* next;
        int index;
        explicit Node(int index, double prob = 0, Node* next = nullptr)
            : index(index), probability(prob), next(next) {}
    };

    Node* head = new Node(-1);
    Node* pre = head;
    // 将每个概率乘以n，所有概率总和为n
    for (int i = 0; i < n; i++) {
        pre->next = new Node(i,weighted_list[i] * n);
        pre = pre->next;
    }

    // 构建alias table
    for (int i = 0; i < n - 1; i++) {
        // 在head链表中，查找概率<=1的节点
        Node* first = nullptr;
        Node* cur = head;
        while (cur->next) {
            if (cur->next->probability <= 1) {
                first = cur->next;
                // 删除cur节点
                cur->next = cur->next->next;
                break;
            } else {
                cur = cur->next;
            }
        }
        // 在head链表中，查找概率>=1的节点
        Node* second = nullptr;
        cur = head;
        while (cur->next) {
            if (cur->next->probability >= 1) {
                second = cur->next;
                // 删除cur节点
                cur->next = cur->next->next;
                break;
            } else {
                cur = cur->next;
            }
        }
        // second有可能为nullptr，是浮点运算精度导致的

        prob_table[first->index] = first->probability;
        alias_table[first->index] = second->index;
        // 修正second节点的概率
        second->probability = second->probability - (1 - first->probability);
        second->next = head->next;
        head->next = second;
    }
    // 如果浮点运算精度运算正确，head链表只存在一个有效节点，该节点的概率一定是等于1（由于浮点运算精度问题，实际上可能是接近1）
    prob_table[n - 1] = head->next->probability;

    srand(seed);
    // 开始抽样
    for (int i = 0; i < m; i++) {
        int index = rand() % n;
        double k = (double) rand() / RAND_MAX;
        if (k < prob_table[index]) {
            result_list[i] = index;
        } else {
            result_list[i] = alias_table[i];
        }
    }

    delete []alias_table;
    delete []prob_table;
}

void
RandomSampling::weighted_random_sample_alias_method_bst(int n, const double *weighted_list, int m, int *result_list) {
    // 基于weighted_random_sample_alias_method_navie进行改进
    // 采用bst，每次查找最大和最小概率，构建alias表，复杂度从O(n)降为O(log(n))
}

void
RandomSampling::weighted_random_sample_alias_method_vose(int n, const double *weighted_list, int m, int *result_list) {
    auto* alias_table = new int[n];
    auto* prob_table = new double[n];

    struct Node {
        int index;
        double probability;
        explicit Node(int index, double probability) : index(index), probability(probability) {}
    };

    // 存储概率<1的节点
    std::stack<Node> small;
    // 存储概率>=1的节点
    std::stack<Node> large;

    // 将每个概率乘以n，所有概率总和为n
    for (int i = 0; i < n; i++) {
        double probability = weighted_list[i] * n;
        if (probability < 1) {
            small.emplace(i, probability);
        } else {
            large.emplace(i, probability);
        }
    }

    while (!small.empty() && !large.empty()) {
        auto small_node = small.top();
        small.pop();
        auto large_node = large.top();
        large.pop();

        prob_table[small_node.index] = small_node.probability;
        alias_table[small_node.index] = large_node.index;
        // large_node节点的剩余概率
        double left_prob = large_node.probability - (1 - small_node.probability);
        if (left_prob < 1) {
            small.emplace(large_node.index, left_prob);
        } else {
            large.emplace(large_node.index, left_prob);
        }
    }

    // 算法分析：在理论上，small为空，large一定仅存在一个节点，且该节点概率为1
    // 但在实际上，由于浮点运算精度问题，最后一个节点可能存在于small！

    // 如果large非空，则small一定为空
    // 剩余节点的概率一定是等于1（由于浮点运算精度问题，实际上可能是接近1）
    while (!large.empty()) {
        auto cur = large.top();
        large.pop();
        prob_table[cur.index] = 1;
    }
    // 如果small非空，则large一定为空
    // 理想上，small就应该是空的，但实际上，由于浮点运算精度问题，某些应该归属large的节点被归为small
    while (!small.empty()) {
        auto cur = small.top();
        small.pop();
        // cur的概率一定是等于1（由于浮点运算精度问题，实际上可能是接近1）
        prob_table[cur.index] = 1;
    }

    srand(seed);
    // 开始抽样
    for (int i = 0; i < m; i++) {
        int index = rand() % n;
        double k = (double) rand() / RAND_MAX;
        if (k < prob_table[index]) {
            result_list[i] = index;
        } else {
            result_list[i] = alias_table[i];
        }
    }

    delete []alias_table;
    delete []prob_table;
}
