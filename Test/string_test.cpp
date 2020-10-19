# include <iostream>
# include "../Amachi_STL/AMI_string"
# include "string"

int main() {
    AMI_std::string test(4, "1234");
    AMI_std::string test2(4, "4321");
    for (auto &i : test) {
        std::cout << i;
    }
    if (!test.compare(test2)) std::cout << "yes";
    std::cout << test.length();
    std::cout << *test.find_first_of('a');
    return 0;
}