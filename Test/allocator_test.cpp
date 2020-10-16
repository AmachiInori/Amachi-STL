# include <vector>
# include <iostream>
# include "../Amachi_STL/AMI_allocate"

int main() {
    std::vector<int, AMI_std::base_allocator<int>> test = {1, 2, 3, 4, 6};
    for (auto &a : test) {
        std::cout << a;
    }
    std::vector<int, AMI_std::base_allocator<int>> test2 = {1, 2};
    for (auto &a : test2) {
        std::cout << a;
    }
    std::vector<long long int, AMI_std::base_allocator<long long int>> test3 = {1, 2, 1, 2, 3, 4, 6,1, 2, 3, 4, 6,1, 2, 3, 4, 6,1, 2, 3, 4, 6};
    for (auto &a : test3) {
        std::cout << a;
    }
    std::vector<int, AMI_std::base_allocator<int>> test4 = {1, 2};
    for (auto &a : test4) {
        std::cout << a;
    }
    return 0;
}