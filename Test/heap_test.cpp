# include "../Amachi_STL/AMI_vector.hpp"
# include "../Amachi_STL/AMI_base/AMI_heap.h"

using namespace AMI_std;

int main() {
    vector<int> testV = {12,13,15,6,3,8,9,10,7};
    build_heap(testV.begin(), testV.end());
    testV.print();
    pop_heap(testV.begin(), testV.end());
    testV.print();
    pop_heap(testV.begin(), testV.end() - 1);
    testV.print();
    pop_heap(testV.begin(), testV.end() - 2);
    testV.print();
    pop_heap(testV.begin(), testV.end() - 3);
    testV.print();
    pop_heap(testV.begin(), testV.end() - 4);
    testV.print();
}