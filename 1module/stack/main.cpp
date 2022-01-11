#include "iostream"
#include <algorithm>
#include <memory>
template<typename T>
class Stack {
private:
    std::unique_ptr<T[]> stackPtr;// указатель на стек
    int size;                     // размер стека
    int top;                      // номер текущего элемента стека
public:
    Stack();
    void push(const T value);// поместить элемент в стек
    T pop();                 // удалить из стека элемент
    void print(std::ostream &out);
    void setSize(int n);
};
template<typename T>
Stack<T>::Stack() : stackPtr{nullptr}, size{0}, top{-1} {
}

template<typename T>
void Stack<T>::setSize(int n) {
    size = n;
    stackPtr.reset(new T[n]);
}

template<typename T>
void Stack<T>::push(const T value) {
    if (top >= size - 1)
        throw std::out_of_range("overflow");
    else {
        ++top;
        stackPtr[top] = value;
    }
}

template<typename T>
T Stack<T>::pop() {
    if (top == -1) {
        throw std::out_of_range("underflow");
    }
    int res = top;
    --top;
    return stackPtr[res];
}
template<typename T>
void Stack<T>::print(std::ostream &out) {
    if (top == -1)
        out << "empty";
    else {
        out << stackPtr[0];
        for (int i = 1; i <= top; ++i)
            out << ' ' << stackPtr[i];
    }
}

int main() {
    Stack<std::string> s;
    s.setSize(5);
    std::string str;
    bool setFlag = true;
    while (std::getline(std::cin, str)) {
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
            std::cout << "error\n";
            continue;
        }
        if (!setFlag) {
            if ((str.substr(0, space - 1)) == "push") {
                if (str.substr(space).find(' ') != std::string::npos) {
                    std::cout << "error\n";
                    continue;
                }
                if (str == "push") {
                    std::cout << "error\n";
                    continue;
                }
                try {
                    s.push(str.substr(space));
                    continue;
                } catch (std::out_of_range) {
                    std::cout << "overflow\n";
                    continue;
                }
            }
            if (str == "print") {
                s.print(std::cout);
                std::cout << "\n";
                continue;
            }
            if (str == "pop") {
                try {
                    std::cout << s.pop() << "\n";
                    continue;
                } catch (std::out_of_range) {
                    std::cout << "underflow\n";
                    continue;
                }
            }
            std::cout << "error\n";
        } else
            std::cout << "error\n";
    }
}