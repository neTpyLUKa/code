#include <iostream>
#include <vector>
#include <algorithm>

struct obj {
    int i_from = 0, j_from = 0, item_number = 0;

    obj() {
    }

    obj(int _i_from, int _j_from, int _item_number) : i_from(_i_from),
                                                      j_from(_j_from), item_number(_item_number) {
    }
};

struct item {
    int weight, price, number;
};

bool operator<(item lhs, item rhs) {
    return lhs.weight < rhs.weight;
}

int main() {
    int n_items, max_weight;
    std::cin >> n_items >> max_weight;
    std::vector<item> items(n_items + 1);
    for (int i = 1; i <= n_items; ++i) {
        std::cin >> items[i].weight;
        items[i].number = i;
    }
    for (int i = 1; i <= n_items; ++i) {
        std::cin >> items[i].price;
    }
    std::sort(items.begin(), items.end());
    std::vector<std::vector<int>> backpack(n_items + 1, std::vector<int>(max_weight + 1, 0));
    std::vector<std::vector<obj>> last_item(n_items + 1, std::vector<obj>(max_weight + 1));
    for (int i = 1; i <= n_items; ++i) {
        for (int j = 1; j <= max_weight; ++j) {
            if (j >= items[i].weight) {
                if (backpack[i - 1][j] > backpack[i - 1][j - items[i].weight] + items[i].price) {
                    backpack[i][j] = backpack[i - 1][j];
                    last_item[i][j] = obj(i - 1, j, 0);
                } else {
                    backpack[i][j] = backpack[i - 1][j - items[i].weight] + items[i].price;
                    last_item[i][j] = obj(i - 1, j - items[i].weight, items[i].number);
                }
            } else {
                backpack[i][j] = backpack[i - 1][j];
                last_item[i][j] = obj(i - 1, j, 0);
            }
        }
    }
    int i = n_items;
    int j = max_weight;
    std::vector<int> res;
    while (i != 0 && j != 0) {
        if (last_item[i][j].item_number != 0) {
            res.push_back(last_item[i][j].item_number);
        }
        int tmp = i;
        i = last_item[i][j].i_from;
        j = last_item[tmp][j].j_from;
    }
    std::sort(res.begin(), res.end());
    for (auto i : res) {
        std::cout << i << '\n';
    }
    return 0;
}
