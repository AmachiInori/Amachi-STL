# include <iostream>
# include <vector>
# include <array>
# include "../Amachi_STL/AMI_allocate.hpp"
# include "../Amachi_STL/AMI_array.hpp"

int main() {
    AMI_std::array<int, 4> test(3);
    for (auto i : test) {
        std::cout << i;
    }
    return 0;
}