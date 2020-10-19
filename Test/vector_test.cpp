# include <iostream>
# include "../Amachi_STL/AMI_allocate"
# include "../Amachi_STL/AMI_vector"

int main() {
    int i = 0;
    int table[5] = {1, 2, 3, 4, 5};
    AMI_std::vector<int> test(table, table + 5); //必须是引用？
    test.insert(3, 100, 9);
    test.erase(3, 102);
    test.reverse();
    test.clear();
    test.resize(12, 3);
    for (auto &i : test) {
        std::cout << i;
    }
    return 0;
}