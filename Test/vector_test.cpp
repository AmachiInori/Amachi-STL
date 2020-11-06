# define AMI_STL_STRICT_MODE
# include <iostream>
# include <vector>
# include "../Amachi_STL/AMI_allocate.hpp"
# include "../Amachi_STL/AMI_vector.hpp"

int main() {
    AMI_std::vector<int> test = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    std::cout << test[9];
    return 0;
}