#include <iostream>
#include <vector>
#include <algorithm>

void insert(std::vector<int> &heap, int elem, int &push_to) {
    heap[push_to] = elem;
    int cur_pos = push_to;
    while (heap[push_to] != INT32_MIN) {
        ++push_to;
    }
    while (heap[(cur_pos - 1) / 2] < heap[cur_pos]) {
        std::swap(heap[(cur_pos - 1) / 2], heap[cur_pos]);
        cur_pos = (cur_pos - 1) / 2;
    }
}

int get_max(std::vector<int> &heap, int &push_to) {
    int ans = heap[0];
    int cur_pos = 0;
    --push_to;
    heap[cur_pos] = heap[push_to];
    heap[push_to] = INT32_MIN;
    while (heap[cur_pos * 2 + 1] > heap[cur_pos]
           || heap[cur_pos * 2 + 2] > heap[cur_pos]) {
        if (heap[cur_pos * 2 + 1] > heap[cur_pos * 2 + 2]) {
            std::swap(heap[cur_pos], heap[cur_pos * 2 + 1]);
            cur_pos = cur_pos * 2 + 1;
        } else {
            std::swap(heap[cur_pos], heap[cur_pos * 2 + 2]);
            cur_pos = cur_pos * 2 + 2;
        }
    }
    return ans;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> heap(2 * n, INT32_MIN);
    int push_to = 0;
    for (size_t i = 0; i < n; ++i) {
        int operation;
        std::cin >> operation;
        if (operation == 0) {
            int tmp;
            std::cin >> tmp;
            insert(heap, tmp, push_to);
        } else {
            std::cout << get_max(heap, push_to) << "\n";
        }
    }
    return 0;
}
