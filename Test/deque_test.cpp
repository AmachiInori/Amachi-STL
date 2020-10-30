# include <iostream>
# include <vector>
# include <deque>
# include "../Amachi_STL/AMI_deque.hpp"

int main() {
    AMI_std::deque<int> test = {1, 2, 3, 4, 5};
    std::cout << test.size();
    test.insert(test.begin() + 2, 10);
    for (auto a : test) {
        std::cout << a << " ";
    }
    return 0;
}