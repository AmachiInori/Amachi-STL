# include <vector>
# include <iostream>
# include "../Amachi_STL/AMI_allocate"

class Solution {
    std::vector<std::vector<int>, AMI_std::base_allocator<int>> res;
    std::vector<int, AMI_std::base_allocator<int>> temp;
public:
    void runner(std::vector<int>& candidates, int target, int lastPlace){
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

    std::vector<std::vector<int>, AMI_std::base_allocator<int>> combinationSum
        (std::vector<int>& candidates, int target) {
        temp = std::vector<int, AMI_std::base_allocator<int>>(candidates.size(), 0);
        runner(candidates, target, 0);
        return res;
    }
};

int main() {
    Solution s;
    std::vector<int> test = {1, 2, 4, 8, 16, 32, 64, 128, 256};
    s.combinationSum(test, 100);
    return 0;
}
