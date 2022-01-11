//
// Created by oleg on 14.12.2021.
//
#include "iostream"
#include <valarray>
#include <vector>
const long int kMersenne = 2147483647;
class BloomFilter {
public:
    void add(unsigned long long int k);
    void print(std::ostream &out);
    void getMK(std::ostream &out) const;
    bool search(unsigned long long int k);
    void init(long long int n, double P);

private:
    int hash;
    std::vector<bool> arr;
    std::vector<int> prime{2};
};

void BloomFilter::add(unsigned long long int k) {
    k = k % kMersenne;
    for (uint64_t i = 0; i < hash; ++i) {
        auto intex = (((i + 1) * k + prime[i]) % kMersenne) % arr.size();
        arr[intex] = true;
    }
}


void BloomFilter::print(std::ostream &out) {
    for (const auto &element : arr) {
        out << element;
    }
    out << "\n";
}

bool BloomFilter::search(unsigned long long int k) {
    k = k % kMersenne;
    for (uint64_t i = 0; i < hash; ++i) {
        auto intex = (((i + 1) * k + prime[i]) % kMersenne) % arr.size();
        if (!arr[intex])
            return false;
    }
    return true;
}
void BloomFilter::init(long long int n, double P) {
    if (n <= 0 || P < 0.0 || P > 1.0) {
        throw std::logic_error("error\n");
    }
    int m = round((-1 * n * log2(P)) / log(2));//размер массива
    hash = round(-1 * log2(P));                //кол-во хешей
    arr.resize(m);
    if (arr.empty() || hash == 0) {
        throw std::logic_error("error\n");
    }
    int p = 2;
    bool flagPrime = true;
    while (prime.size() < hash + 1) {
        flagPrime = true;
        p++;
        for (int i = 0; (i < prime.size() && prime[i] <= p * p); ++i) {
            if (p % prime[i] == 0)
                flagPrime = false;
        }
        if (flagPrime)
            prime.push_back(p);
    }
}

void BloomFilter::getMK(std::ostream &out) const {
    out << arr.size() << " " << hash << "\n";
}
int main() {
    std::ios_base::sync_with_stdio(false);
    BloomFilter myBloom;
    std::string str;
    bool setFlag = false;
    while (std::getline(std::cin, str)) {
        auto nagativ = str.find('-');
        auto space = str.find(' ');
        auto spaceZero = str.find(" 0.");

        if (str.empty())
            continue;
        if (nagativ != std::string::npos) {
            std::cout << "error\n";
            continue;
        }
        auto foundSet = str.find("set");
        if (foundSet != std::string::npos && setFlag) {
            std::cout << "error\n";
            continue;
        }
        if (foundSet != std::string::npos) {
            try {
                auto m = std::stoull(str.substr(space, spaceZero));
                auto k = std::stod(str.substr(spaceZero));
                myBloom.init(m, k);
                myBloom.getMK(std::cout);
                setFlag = true;
            } catch (std::invalid_argument) {
                std::cout << "error\n";
                continue;
            } catch (std::logic_error) {
                std::cout << "error\n";
                continue;
            }
        }
        if (setFlag) {
            auto foundAdd = str.find("add");
            if (foundAdd != std::string::npos) {
                unsigned long long int num = std::stoull(str.substr(space));
                myBloom.add(num);
            }
            auto foundSearch = str.find("search");
            if (foundSearch != std::string::npos) {
                unsigned long long int num = std::stoull(str.substr(space));
                if (myBloom.search(num)) {
                    std::cout << "1\n";
                } else
                    std::cout << "0\n";
            }
            auto foundPrint = str.find("print");
            if (foundPrint != std::string::npos) {
                myBloom.print(std::cout);
            }
        } else
            std::cout << "error\n";
    }
}