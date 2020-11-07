//# define AMI_STRICT_MODE_ON
# include <iostream>
# include <vector>
# include "../Amachi_STL/AMI_allocate.hpp"
# include "../Amachi_STL/AMI_vector.hpp"

AMI_std::vector<int> getV() { 
    AMI_std::vector<int> a(5, 3);
    a[1] = 2;
    return a;
}

int main() {
    AMI_std::vector<std::vector<int>> a{{1,2},{2,3}};
    AMI_std::vector<int> d(1,2);
    std::vector<int> i = {1,2,3};
    std::vector<int> j = {1,2};
    i = j;
    return 0;
}