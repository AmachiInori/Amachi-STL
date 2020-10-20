# include <iostream>
# include "../Amachi_STL/AMI_allocate"
# include "../Amachi_STL/AMI_vector"

int main() {
    int i = 0;
    AMI_std::vector<int> test = {1, 2, 3, 4, 5}; //必须是引用？
    test.print();
    test.reverse();
    std::cout << test;
    return 0;
}