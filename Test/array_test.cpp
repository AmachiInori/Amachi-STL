# include <iostream>
# include "../Amachi_STL/AMI_allocate.hpp"
# include "../Amachi_STL/AMI_array.hpp"

int main() {
    AMI_std::array<int> test = {1,2,3,4,5,6};
    for (auto i : test) {
        std::cout << i;
    }
    return 0;
}