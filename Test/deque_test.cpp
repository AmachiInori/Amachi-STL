# include <iostream>
# include <vector>
# include <deque>
# include "../Amachi_STL/AMI_deque.hpp"

int main() {
    AMI_std::deque<int> test1({1,2,3,4,5,6,6,7});
    AMI_std::deque<int> test(std::move(test1));
    test.print();
    return 0;
}