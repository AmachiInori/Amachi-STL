# include <iostream>
# include <vector>
# include "../Amachi_STL/AMI_allocate.hpp"
# include "../Amachi_STL/AMI_array.hpp"

int main() {
    std::vector<int> tst = {1,2,3,4,5};
    AMI_std::array<int> test = tst;
    for (auto i : test) {
        std::cout << i;
    }
    return 0;
}