# include <iostream>
# include <vector>
# include <deque>
# include "../Amachi_STL/AMI_deque.hpp"

int main() {
    AMI_std::deque<int> test = {1, 2, 3, 4, 5};
    for (int i = 0; i < 1000; i++) 
        test.push_front(6);
    test.clear();
    for (int i = 0; i < 14; i++) 
        test.push_front(7);
    for (auto a : test) {
        std::cout << a;
    }
    return 0;
}