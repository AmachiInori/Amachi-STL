# include <iostream>
# include <vector>
# include "../Amachi_STL/AMI_allocate"
# include "../Amachi_STL/AMI_vector"

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
    s.combinationSum(test, 150).print();

    int i = 0;
    vector<int> test1 = {1, 2, 3, 4, 5};
    test.print();
    test.reverse();
    std::cout << test;
    return 0;
}
