#include <iostream>
#include <string>

int main() {
    std::string str;
    int64_t sum = 0;
    std::string num = {};
    while (std::getline(std::cin, str)) {
        if (str.empty()) continue;
        for (int64_t i = 0; i < str.size(); ++i) {
            if (str[i] == '-' && isdigit(str[i + 1])) {
                num += '-';
            }
            if (!isdigit(str[i])) {
                continue;
            }
            if (isdigit(str[i])) {
                num += str[i];
            }
            if (isdigit(str[i]) && !isdigit(str[i + 1])) {
                sum += std::stoll(num);
                num = {};
            }
        }
    }
    std::cout << sum;
}