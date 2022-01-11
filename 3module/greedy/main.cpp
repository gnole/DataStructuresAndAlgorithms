#include "iostream"
#include "vector"


int count(int num, int seed) {
    if (num % 2 == 0)
        return count(num / 2, seed + 1);
    else
        return seed;
}

int foo(int n, std::vector<std::string> &res) {
    while (n > 1 && n != 3) {
        while (n % 2 == 0) {
            res.push_back("dbl");
            n = n / 2;
        }
        if (n == 1) {
            res.push_back("inc");
            n = n - 1;
            break;
        }
        if (n == 3) {
            res.push_back("inc");
            res.push_back("dbl");
            res.push_back("inc");
            n = 0;
            break;
        }
        if (count(n + 1, 0) > count(n - 1, 0)) {
            res.push_back("dec");
            n = n + 1;

        } else {
            res.push_back("inc");
            n = n - 1;
        }
    }
    if (n == 1) {
        res.push_back("inc");
        n = n - 1;
    }
    if (n == 3) {
        res.push_back("inc");
        res.push_back("dbl");
        res.push_back("inc");
        n = 0;
    }
}

int main() {

    std::vector<std::string> res;
    int n;
    std::cin >> n;

    foo(n, res);
    for (auto it = res.end() - 1; it >= res.begin(); it--) {
        std::cout << *it << std::endl;
    }
}