#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string req, word, trash;
    std::cin >> req >> word;
    std::getline(std::cin, trash);
    std::string tmp;
    std::vector<std::string> is_included;
    std::vector<std::string> not_included;
    while (getline(std::cin, tmp)) {
        if (tmp.find(word, 0) != std::string::npos) {
            is_included.push_back(tmp);
        } else {
            not_included.push_back(tmp);
        }
    }
    if (req == "-f") {
        for (auto str : is_included) {
            std::cout << str << std::endl;
        }
    } else {
        for (auto str : not_included) {
            std::cout << str << std::endl;
        }
    }
    return 0;
}
