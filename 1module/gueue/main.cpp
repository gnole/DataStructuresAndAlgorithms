#include "iostream"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <vector>

template<typename T>
class Queue {
private:
    std::unique_ptr<T[]> stackPtr;
    int size; // размер очереди
    int begin;// начало очереди
    int end;  // конец очереди
    bool isFull();

public:
    Queue();
    void push(const T value);
    T pop();
    void print(std::ostream &out);
    void setSize(int n);
};
template<typename T>
Queue<T>::Queue() : stackPtr{nullptr}, size{0}, begin{-1}, end{-1} {
}

template<typename T>
void Queue<T>::setSize(int n) {
    size = n;
    stackPtr.reset(new T[n]);
}

template<typename T>
void Queue<T>::push(const T value) {
    if (isFull())
        throw std::out_of_range("overflow");
    else {
        if (begin == -1) begin = 0;
        ++end %= size;
        stackPtr[end] = value;
    }
}

template<typename T>
T Queue<T>::pop() {
    if (begin == -1) {
        throw std::out_of_range("underflow");
    }
    const int res = begin;
    if (begin == end) {
        begin = -1;
        end = -1;
    } else
        ++begin %= size;
    return stackPtr[res];
}
template<typename T>
void Queue<T>::print(std::ostream &out) {
    if (begin == -1)
        out << "empty";
    else {
        int i = begin;
        for (; i != end; ++i %= size)
            out << stackPtr[i] << ' ';
        out << stackPtr[i];
    }
}
template<typename T>
bool Queue<T>::isFull() {
    if (begin == 0 && end == size - 1)
        return true;
    if (begin == end + 1)
        return true;
    return false;
}

int main(int argc, char *argv[]) {
    std::ifstream in(argv[1]);
    Queue<std::string> s;
    std::string str;
    bool setFlag = true;
    std::ofstream out(argv[2]);
    while (std::getline(in, str)) {
        if (str.empty())
            continue;
        auto space = str.find(' ') + 1;
        auto foundSet = str.find("set_size");
        if (foundSet != std::string::npos && setFlag) {
            setFlag = false;
            s.setSize(std::stoi(str.substr(space)));
            continue;
        }
        if (foundSet != std::string::npos) {
            out << "error\n";
            continue;
        }
        if (!setFlag) {
            if ((str.substr(0, space - 1)) == "push") {
                if (str.substr(space).find(' ') != std::string::npos) {
                    out << "error\n";
                    continue;
                }
                if (str == "push") {
                    out << "error\n";
                    continue;
                }
                try {
                    s.push(str.substr(space));
                    continue;
                } catch (std::out_of_range) {
                    out << "overflow\n";
                    continue;
                }
            }
            if (str == "print") {
                s.print(out);
                out << "\n";
                continue;
            }
            if (str == "pop") {
                try {
                    out << s.pop() << "\n";
                    continue;
                } catch (std::out_of_range) {
                    out << "underflow\n";
                    continue;
                }
            }
            out << "error\n";
        } else
            out << "error\n";
    }
    in.close();
    out.close();
}
