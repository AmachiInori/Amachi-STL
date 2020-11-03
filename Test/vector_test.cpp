# include <iostream>
# include <vector>
# include "../Amachi_STL/AMI_allocate.hpp"
# include "../Amachi_STL/AMI_vector.hpp"

int main() {
    std::vector<int> test = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    AMI_std::vector<int> testr = {1,2};
    testr = test;
    testr.insert(5, 2, 3);
    testr.print();
    return 0;
}