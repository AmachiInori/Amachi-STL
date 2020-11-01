# include <iostream>
# include <vector>
# include "../Amachi_STL/AMI_allocate.hpp"
# include "../Amachi_STL/AMI_vector.hpp"

using AMI_std::vector;

class Solution {
    vector<vector<int>> res;
    vector<int> temp;
public:
    void runner(vector<int>& candidates, int target, int lastPlace){
        if (target == 0) {
            res.push_back({});
            for (int i = 0; i < temp.size(); i++) {
                for (int j = 0; j < temp[i]; j++) {
                    res.back().push_back(candidates[i]);
                }
            }
            return;
        }
        if (target < 0) return;
        for (int i = lastPlace; i < candidates.size(); i++) {
            temp[i]++;
            runner(candidates, target - candidates[i], i);
            temp[i]--;
        }
        return;
    } 

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        temp = vector<int>(candidates.size(), 0);
        runner(candidates, target, 0);
        return res;
    }
};

int main() {
    Solution s;
    vector<int> test = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    vector<int> testr;
    testr = test;
    test.insert(5, 2, 3);
    test.print();
    return 0;
}
