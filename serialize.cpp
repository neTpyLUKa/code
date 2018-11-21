#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

template <typename T>
void Serialize(T pod, std::ostream& out);

void Serialize(const std::string& str, std::ostream& out);

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out);

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out);



template <typename T>
void Deserialize(std::istream& in, T& pod);

void Deserialize(std::istream& in, std::string& str);

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data);

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data);

template <typename T>
void Deserialize(std::istream& in, T& pod) {
    std::string str(sizeof(T), '\0');
    in.read(&str[0], sizeof(T));
    pod = *reinterpret_cast<T*>(&str[0]);
}

void Deserialize(std::istream& in, std::string& str) {
    size_t size;
    Deserialize(in, size);
    std::string string(size, '\0');
    in.read(&string[0], size);
    str = string;
}

template <typename T>
void Deserialize(std::istream& in, std::vector<T>& data) {
    size_t size;
    Deserialize(in, size);
    data.resize(size);
    for (size_t i = 0; i < size; ++i) {
        Deserialize(in, data[i]);
    }
}

template <typename T1, typename T2>
void Deserialize(std::istream& in, std::map<T1, T2>& data) {
    size_t size;
    Deserialize(in, size);
    for (size_t i = 0; i < size; ++i) {
        T1 a;
        T2 b;
        Deserialize(in, a);
        Deserialize(in, b);
        data[a] = b;
    }
}

template <typename T>
void Serialize(T pod, std::ostream& out) {
    out.write(reinterpret_cast<const char*>(&pod), sizeof(T));
}

void Serialize(const std::string& str, std::ostream& out) {
    Serialize(str.length(), out);
    out.write(reinterpret_cast<const char*>(&str[0]), str.length());
}

template <typename T>
void Serialize(const std::vector<T>& data, std::ostream& out) {
    Serialize(data.size(), out);
    for (size_t i = 0; i < data.size(); ++i) {
        Serialize(data[i], out);
    }
}

template <typename T1, typename T2>
void Serialize(const std::map<T1, T2>& data, std::ostream& out) {
    Serialize(data.size(), out);
    for (auto i : data) {
        Serialize(i.first, out);
        Serialize(i.second, out);
    }
}

