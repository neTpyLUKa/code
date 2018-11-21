#include <iostream>
#include <vector>
#include <algorithm>

template<class T>
class Polynomial {
private:
    std::vector <T> coeffs;
public:
    Polynomial(const std::vector <T> &vec) {
        coeffs = vec;
    }

    template<typename it>
    Polynomial(it first, it last) {
        while (first != last) {
            coeffs.push_back(*first++);
        }
    }

    Polynomial(const T &a = T(0)) {
        coeffs.push_back(a);
    }

    T operator[](const int &a) const {
        if (a >= static_cast<int>(coeffs.size())) {
            return T(0);
        }
        return coeffs[a];
    }

    size_t Degree() const {
        size_t i = coeffs.size();
		i--;
        for (i; i != -1 && coeffs[i] == T(0); --i) {}
        return i;
    }

    bool operator==(const Polynomial<T> &other) const {
        size_t bound = std::min(coeffs.size() - 1, other.Degree());
        size_t i = -1;
        while (i++ < bound) {
            if (coeffs[i] != other[i]) {
                return false;
            }
        }
        if (coeffs.size() > other.Degree()) {
            while (i != static_cast<int>(coeffs.size())) {
                if (coeffs[i] != T(0)) {
                    return false;
                }
                ++i;
            }
        } else {
            return false;
        }
        return true;
    }

    bool operator!=(const Polynomial<T> &other) const {
        return !(*this == other);
    }

    Polynomial<T> operator+(const Polynomial<T> &other) const {
        size_t bound = std::min(coeffs.size() - 1, other.Degree());
        std::vector <T> vec;
        size_t i = -1;
        while (i++ < bound) {
            vec.push_back(other[i] + coeffs[i]);
        }
        for (i; i < coeffs.size(); ++i) {
            vec.push_back(coeffs[i]);
        }
        for (i; i <= other.Degree(); ++i) {
            vec.push_back(other[i]);
        }
        return Polynomial<T>(vec);
    }

    Polynomial<T> operator+(const T &other) const {
        return *this + Polynomial<T>(other);
    }

    Polynomial<T>& operator+=(const Polynomial<T> &other) {
        *this = *this + other;
        return *this;
    }

    Polynomial<T>& operator+=(const T &other) {
        *this = *this + Polynomial<T>(other);
        return *this;
    }

    Polynomial<T> operator-(const Polynomial<T> &other) const {
        size_t bound = std::min(coeffs.size() - 1, other.Degree());
        std::vector <T> vec;
        size_t i = -1;
        while (i++ < bound) {
            vec.push_back(coeffs[i] - other[i]);
        }
        for (i; i < coeffs.size(); ++i) {
            vec.push_back(coeffs[i]);
        }
        for (i; i <= other.Degree(); ++i) {
            vec.push_back(T(0) - other[i]);
        }
        return Polynomial<T>(vec);
    }

    Polynomial<T>& operator-=(const Polynomial<T> &other) {
        *this = *this - other;
        return *this;
    }

    Polynomial<T> operator-(const T &other) const {
        return *this - Polynomial<T>(other);
    }

    Polynomial<T>& operator-=(const T &other) {
        *this = *this - Polynomial<T>(other);
        return *this;
    }

    typename std::vector<T>::const_iterator begin() const {
        return coeffs.begin();
    }

    typename std::vector<T>::const_iterator end() const {
        return coeffs.end();
    }

    Polynomial<T> operator*(const T &other) const {
        std::vector<T> res = coeffs;
        for (size_t i = 0; i < static_cast<int>(res.size()); ++i) {
            res[i] *= other;
        }
        return Polynomial<T>(res);
    }

    Polynomial<T>& operator*=(const T &other) {
        for (size_t i = 0; i < static_cast<int>(coeffs.size()); ++i) {
            coeffs[i] *= other;
        }
        return *this;
    }

    Polynomial<T> operator*(const Polynomial<T> &other) const {
        if (other.Degree() >= coeffs.size()) {
            return other * (*this);
        }
        Polynomial<T> res;
        for (size_t i = 0; i < coeffs.size(); ++i) {
            std::vector<T> tmp_vec(coeffs.size() + i, T(0));
            for (size_t j = 0; j < coeffs.size(); ++j) {
                tmp_vec[j + i] = coeffs[j];
            }
            res += Polynomial<T>(tmp_vec) * other[i];
        }
        return res;
    }

    Polynomial<T>& operator*=(const Polynomial<T> &other) {
        Polynomial<T> res;
        for (size_t i = 0; i < coeffs.size(); ++i) {
            std::vector<T> tmp_vec(coeffs.size() + i, T(0));
            for (size_t j = 0; j < coeffs.size(); ++j) {
                tmp_vec[j + i] = coeffs[j];
            }
            res += Polynomial<T>(tmp_vec) * other[i];
        }
        *this = res;
        return *this;
    }

    T operator()(const T &point) const {
        T res = T(0);
        for (size_t i = coeffs.size() - 1; i >= 0; --i) {
            res *= point;
            res += coeffs[i];
        }
        return res;
    }

    Polynomial<T> operator&(const Polynomial<T> &other) const {
    	Polynomial<T> res(coeffs[coeffs.size() - 1]);
    	for (int i = coeffs.size() - 2; i >= 0; --i) {
    		res = other * res;
    		res += Polynomial<T>(coeffs[i]);
		}
		return res;
	}
};

template<typename T>
Polynomial<T> operator*(const T &other, const Polynomial<T> &self) {
    return self * other;
}

template<typename T>
Polynomial<T> operator+(const T &other, const Polynomial<T> &self) {
    return self + other;
}

template<typename T>
Polynomial<T> operator-(const T &other, const Polynomial<T> &self) {
    return Polynomial<T>(other) - self;
}

template<typename T>
std::ostream &operator<<(std::ostream &out, const Polynomial<T> &pol) {
    if (pol.Degree() == -1) {
        out << 0;
    } else if (pol.Degree() == 0) {
        out << pol[0];
    } else if (pol.Degree() == 1) {
        if (pol[1] == T(-1)) {
            out << "-";
        } else if (pol[1] == T(1)) {} else {
            out << pol[1] << "*";
        }
        out << "x";
        if (pol[0] != T(0)) {
                if (pol[0] > T(0)) {
                    out << "+";
                }
            out << pol[0];
        }
    } else {
        if (pol[pol.Degree()] == T(-1)) {
            out << "-x^" << pol.Degree();
        } else if (pol[pol.Degree()] == T(1)) {
            out << "x^" << pol.Degree();
        } else {
            out << pol[pol.Degree()] << "*x^" << pol.Degree();
        }
        for (int i = pol.Degree() - 1; i >= 1; --i) {
            if (pol[i] != T(0)) {
                if (pol[i] > T(0)) {
                    out << "+";
                } else if (pol[i] == T(-1)) {
                    out << "-";
                }
                if (pol[i] != T(-1) && pol[i] != T(1)) {
                    out << pol[i] << "*";
                }
                out << "x";
                if (i > 1) {
                    out << "^" << i;
                }
            }
        }
        if (pol[0] != T(0)) {
            if (pol[0] > T(0)) {
                out << "+";
            }
            out << pol[0];
        }
    }
    return out;
}

