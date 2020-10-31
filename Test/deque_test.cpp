# include <iostream>
# include <vector>
# include <deque>
# include "../Amachi_STL/AMI_deque.hpp"

int main() {
    std::vector<int> testv = {1,2,3,4,5,6,6,7};
    AMI_std::deque<int> test(testv);
    AMI_std::deque<int> test2({1,2,3,4,5,6,6,7});
    test.insert(test.begin() + 4, 10);
    test.erase(test.begin() + 4);
    for (auto a : test) {
        std::cout << a << " ";
    }
    return 0;
}