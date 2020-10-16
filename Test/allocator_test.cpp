# include <vector>
# include <iostream>
# include "../Amachi_STL/AMI_alloc.h"

int main() {
    std::vector<int, AMI_std::base_allocator<int>> test = {1, 2};
    for (auto &a : test) {
        std::cout << a;
    }
    return 0;
}