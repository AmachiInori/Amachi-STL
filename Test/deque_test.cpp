# include <iostream>
# include <vector>
# include <deque>
# include "../Amachi_STL/AMI_deque.hpp"

int main() {
    AMI_std::deque<int> test({1,2,3,4,5,6,6,7});
    test.erase(test.begin() + 1, test.end() - 1);
    test.print();
    return 0;
}