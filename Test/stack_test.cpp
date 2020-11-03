# include "../Amachi_STL/AMI_stack.hpp"
# include "../Amachi_STL/AMI_vector.hpp"

int main() {
    AMI_std::vector<int> ori = {1};
    ori.print();
    AMI_std::stack<int> test = ori;
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    test.pop();
    return 0;
}