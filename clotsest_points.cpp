#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>

struct point {
    int x, y;
};

bool comp_x(const point &a, const point &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool comp_y(const point &a, const point &b) {
    return a.y < b.y;
}

std::vector<point> vec(123456);
double min_dist = 1e17;

void upd_ans(const point &a, const point &b) {
    double dist = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
    if (dist < min_dist) {
        min_dist = dist;
    }
}

void get_min(int left, int right) {
    if (right - left <= 3) {
        for (int i = left; i <= right; ++i) {
            for (int j = i + 1; j <= right; ++j) {
                upd_ans(vec[i], vec[j]);
            }
        }
        std::sort(vec.begin() + left, vec.begin() + right + 1, comp_y);
        return;
    }

    int mid = (left + right)  / 2;
    int mid_x = vec[mid].x;
    get_min(left, mid);
    get_min(mid + 1, right);
    static point t[123456];
    std::merge(vec.begin() + left, vec.begin() + mid + 1,
               vec.begin() + mid + 1, vec.begin() + right + 1, t, comp_y);
    std::copy(t, t + right - left + 1, vec.begin() + left);
    int tsz = 0;
    for (int i = left; i <= right; ++i) {
        if (abs(vec[i].x - mid_x) < min_dist) {
            for (int j = tsz - 1; j >= 0 && vec[i].y - t[j].y < min_dist; --j) {
                upd_ans(vec[i], t[j]);
            }
            t[tsz++] = vec[i];
        }
    }
    return;
}

int main() {
    int n;
    std::cin >> n;
    for (size_t i = 0; i < n; ++i) {
        std::cin >> vec[i].x >> vec[i].y;
    }
    std::sort(vec.begin(), vec.begin() + n, comp_x);
    get_min(0, n - 1);
    std::cout << std::setprecision(18) << min_dist;
    return 0;
}
