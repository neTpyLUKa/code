#include <iostream>
#include <vector>

template<class T>
class Matrix {
private:
    std::vector<std::vector<T>> object;

public:
    Matrix<T>(const std::vector<std::vector<T>> &to_set) {
        if (!to_set.empty()) {
            object = std::vector<std::vector<T>>(to_set.size(), std::vector<T>(to_set[0].size()));
        }
        for (size_t i = 0; i < to_set.size(); ++i) {
            for (size_t j = 0; j < to_set[0].size(); ++j) {
                object[i][j] = to_set[i][j];
            }
        }
    }

    std::vector<T>& operator[](size_t i) {
        return object[i];
    }

    const std::vector<T>& operator[](size_t i) const {
        return object[i];
    }

    std::pair<size_t, size_t> size() const {
        if (!object.empty()) {
            if (!object[0].empty()) {
                return std::make_pair(object.size(), object[0].size());
            }
            return std::make_pair(object.size(), 0);
        }
        return std::make_pair(0, 0);
    }

    T get_element(size_t i, size_t j) const {
        return object[i][j];
    }

    Matrix<T> operator+=(const Matrix<T> &m) {
        for (size_t i = 0; i < m.size().first; ++i) {
            for (size_t j = 0; j < m.size().second; ++j) {
                object[i][j] += m.object[i][j];
            }
        }
        return *this;
    }

    Matrix<T> operator+(const Matrix<T> m) const {
        std::vector<std::vector<T>> tmp(m.size().first, std::vector<T>(m.size().second));
        for (size_t i = 0; i < m.size().first; ++i) {
            for (size_t j = 0; j < m.size().second; ++j) {
                tmp[i][j] = object[i][j] + m.object[i][j];
            }
        }
        Matrix<T> res(tmp);
        return res;
    }

    template<typename c>
    Matrix<T> operator*=(c digit) {
        for (size_t i = 0; i < object.size(); ++i) {
            for (size_t j = 0; j < object[i].size(); ++j) {
                object[i][j] *= digit;
            }
        }
        return *this;
    }

    template<typename c>
    Matrix<T> operator*(c m) const {
        std::vector<std::vector<T>> tmp(object.size(), std::vector<T>(object[0].size()));
        for (size_t i = 0; i < object.size(); ++i) {
            for (size_t j = 0; j < object[0].size(); ++j) {
                tmp[i][j] = object[i][j] * m;
            }
        }
        Matrix<T> res(tmp);
        return res;
    }

    Matrix<T> operator*(const Matrix<T> &m) const {
        std::vector<std::vector<T>> vec(this->size().first, std::vector<T>(m.size().second));
        for (size_t i = 0; i < vec.size(); ++i) {
            for (size_t j = 0; j < vec[0].size(); ++j) {
                T tmp = 0;
                for (size_t k = 0; k < this->size().second; ++k) {
                    tmp += object[i][k] * m.object[k][j];
                }
                vec[i][j] = tmp;
            }
        }
        return Matrix(vec);
    }

    Matrix<T> operator*=(const Matrix<T> &m) {
        *this = *this * m;
        return *this;
    }
};

template<class T>
std::ostream &operator<<(std::ostream &out, const Matrix<T> &m) {
    for (size_t i = 0; i < m.size().first; ++i) {
        for (size_t j = 0; j < m.size().second; ++j) {
            out << m.get_element(i, j);
            if (j != m.size().second - 1) {
                out << "\t";
            }
        }
        if (i != m.size().first - 1) {
            out << std::endl;
        }
    }
    return out;
}

