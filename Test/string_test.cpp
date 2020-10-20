# include "../Amachi_STL/AMI_string"
# include <string>
# include <iostream>

int main() {
    AMI_std::string test("abcdef");
    AMI_std::string test2;
    test.to_upper();
    test.reverse();
    std::cout << test.reverse() << "\n";
    return 0;
}