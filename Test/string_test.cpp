# include "../Amachi_STL/AMI_string"
# include <string>
# include <iostream>

int main() {
    AMI_std::string test("12345678");
    AMI_std::string test2("12345678");
    test = test + test2;
    std::cout << test << "\n";
    std::cout << test2 << "\n";
    return 0;
}