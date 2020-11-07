# include "../Amachi_STL/AMI_string.hpp"
# include <string>
# include <iostream>

int main() {
    AMI_std::string test("abcdef");
    AMI_std::string test2(test);
    test = std::move(test2.reverse());
    std::cout << test.reverse() << "\n";
    return 0;
}