# include <iostream>
# include "../Amachi_STL/AMI_allocate"
# include "../Amachi_STL/AMI_vector"

int main() {
    int i = 0;
    AMI_std::vector<int> test(5, i); //必须是引用？
    for (auto &i : test) {
        std::cout << i;
    }
    i = 1;
    test.push_back(i);
    for (auto &i : test) {
        std::cout << i;
    }
    return 0;
}