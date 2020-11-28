# include "../Amachi_STL/AMI_vector.hpp"
# include "../Amachi_STL/AMI_base/AMI_heap.h"

using namespace AMI_std;

int main() {
    vector<int> testV = {2,5,7,1,2,4,8,3,1,5};
    build_heap(testV.begin(), testV.end(), less<int>());
    pop_heap(testV.begin(), testV.end(), less<int>());
    testV.print();
    pop_heap(testV.begin(), testV.end() - 1, less<int>());
    testV.print();
    pop_heap(testV.begin(), testV.end() - 2, less<int>());
    testV.print();
    pop_heap(testV.begin(), testV.end() - 3, less<int>());
    testV.print();
    pop_heap(testV.begin(), testV.end() - 4, less<int>());
    testV.print();
}