#include <iostream>
#include <vector>

std::vector<int> merge(std::vector<int> &vec1, std::vector<int> &vec2) {
    std::vector<int> res;
    size_t i = 0, j = 0;
    for (; i < vec1.size() && j < vec2.size();) {
        if (vec1[i] < vec2[j]) {
            res.push_back(vec1[i]);
            ++i;
        } else {
            res.push_back(vec2[j]);
            ++j;
        }
    }
    for (; i < vec1.size() ; ++i) {
        res.push_back(vec1[i]);
    }
    for (; j < vec2.size() ; ++j) {
        res.push_back(vec2[j]);
    }
    return res;
}

std::vector<int> MergeSort(std::vector<int>::iterator begin,
                           std::vector<int>::iterator end, int n_els) {
    if (n_els == 1) {
        return std::vector<int> {*begin};
    }
    std::vector<int> vec1 = MergeSort(begin, begin + n_els / 2, n_els / 2);
    std::vector<int> vec2 = MergeSort(begin + n_els / 2, end, (n_els + 1) / 2);
    return merge(vec1, vec2);
}

int main() {
    size_t n;
    std::cin >> n;
    if (n > 0) {
        std::vector<int> vec(n);
        for (size_t i = 0; i < n; ++i) {
            std::cin >> vec[i];
        }
        vec = MergeSort(vec.begin(), vec.end(), vec.size());
        for (size_t i = 0; i < n; ++i) {
            std::cout << vec[i] << " ";
        }
    }
}
