# include "../Amachi_STL/AMI_string.hpp"
# include <string>
# include <iostream>

int main() {
    AMI_std::string test("abcdef");
    AMI_std::string test2(test);
    test2 = test;
    std::cout << test.reverse() << "\n";
    return 0;
}