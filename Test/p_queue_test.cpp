# include "../Amachi_STL/AMI_priority_queue.hpp"
# include <iostream>

using namespace AMI_std;

int main() {
    priority_queue<int> test({2, 3, 4, 5, 4, 3, 2, 2});
    std::cout << test.top();
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    std::cout << test.top();
    return 0;
}