
#include "iostream"
#include "vector"
#include <algorithm>
#include <numeric>
#include <regex>

std::vector<size_t> dynamicKnapsack(std::vector<size_t> weight, std::vector<size_t> const &profit, size_t capacity) {
    size_t i, w;
    const size_t size = weight.size();
    std::vector<bool> selected = {0};
    selected.reserve(size);
    std::vector<size_t> res;
    size_t const gcd = std::accumulate(std::next(weight.begin()), weight.end(), weight.front(), std::gcd<size_t, size_t>);
    std::transform(weight.begin(), weight.end(), weight.begin(), [gcd](size_t n) { return n / gcd; });
    capacity = capacity / gcd;
    size_t B[size + 1][capacity + 1];
    for (w = 0; w <= capacity; ++w)
        B[0][w] = 0;
    for (i = 0; i <= size; ++i)
        B[i][0] = 0;


    for (i = 1; i < size + 1; ++i) {
        for (w = 0; w < capacity + 1; ++w) {
            if (weight[i - 1] > w)
                B[i][w] = B[i - 1][w];
            else
                B[i][w] = std::max(B[i - 1][w], B[i - 1][w - weight[i - 1]] + profit[i - 1]);
        }
    }
    for (i = 0; i < size; ++i)
        selected[i] = 0;

    i = size;
    w = capacity;


    while (B[i][w] != 0) {
        if (B[i][w] == B[i - 1][w]) {
            i = i - 1;
        } else {

            selected[i - 1] = 1;
            w = w - weight[i - 1];
            i = i - 1;
        }
    }
    size_t totalWeight = 0;

    for (int long j = size - 1; j >= 0; --j) {
        if (selected[j] == 1) {
            totalWeight += weight[j];
            res.push_back(j + 1);
        }
    }
    size_t totalProfit = B[size][capacity];
    res.push_back(totalProfit);
    res.push_back(totalWeight * gcd);
    return res;
}
void print(std::vector<size_t> &result) {
    size_t i = 0;
    for (auto it = result.end() - 1; it >= result.begin(); --it, ++i) {
        if (i >= 1) {
            std::cout << *it << std::endl;
        } else
            std::cout << *it << " ";
    }
}
int main() {
    std::vector<size_t> weights = {}, profits = {};
    size_t capacity;

    bool flag = false;
    std::string str;
    while (std::getline(std::cin, str)) {
        auto nagativ = str.find('-');
        auto point = str.find('.');

        if (str.empty())
            continue;
        if (nagativ != std::string::npos || point != std::string::npos) {
            std::cout << "error\n";
            continue;
        }
        auto found = str.find(' ');
        if (found == std::string::npos && flag) {
            std::cout << "error\n";
            continue;
        }
        if (found == std::string::npos) {
            try {
                capacity = std::stoull(str);
                flag = true;
            } catch (std::invalid_argument) {
                std::cout << "error\n";
            }
        } else {
            if (flag) {
                try {
                    auto weight = std::stoull(str.substr(0, found)),
                         profit = std::stoull(str.substr(found));
                    if (weight == 0 && profit == 0) {
                        std::cout << "error\n";
                        continue;
                    }
                    weights.push_back(weight);
                    profits.push_back(profit);
                } catch (std::invalid_argument) {
                    std::cout << "error\n";
                }
            } else {
                std::cout << "error\n";
            }
        }
    }
    std::vector<size_t> result = dynamicKnapsack(weights, profits, capacity);
    print(result);
    return 0;
}
