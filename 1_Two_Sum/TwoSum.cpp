/*
 * Given an array of integers, return indices of the two numbers s.t. that they add up
 * to a specific target
 *
 * You may assume that each input would have exactly one solution
 *
 * Example:
 * Given nums = [2, 7, 11, 15], target = 9,
 * return [0, 1] because nums[0] + nums[1] = 2 + 7 = 9
 *
 * */

#include <iostream>
#include <unordered_map>
#include <algorithm>

/*
 * solution 0: sort and compare:
 *  init: sort!(nums), i = 0, j = len - 1,
 *    (I like the julia notation, sort is immutable sort (return copy), sort! is mutable sort (in place) )
 *  algo: if(nums[i] + nums[j] < target) ++i
 *        else if(nums[i] + nums[j] > target) --j
 *        else found
 * time complexity: O(n lgn) + O(n) = O(n lgn)
 *
 * proof of correctness:
 * operator 'x' here means Cartesian product
 * for current search space (i, j) <- [m..n] x [m..n], i < j:
 *   if nums[m] + nums[n] < target, then we can exclude [m] x [m..n]
 *      because nums[m] + nums[j] <= nums[m] + nums[n] < target for any j <- [m..n],
 *      so the new search space become [m+1..n] x [m..n], because i < j, it is
 *      [m+1..n] x [m+1..n]
 *   if nums[m] + nums[n] > target, then we can exclude [m..n] x [n]
 *      because nums[i] + nums[n] >= nums[m] + nums[n] > target for any i <- [m..n],
 *      so the new search space become [m..n] x [m..n-1], because i < j, it is
 *      [m..n-1] x [m..n-1]
 * initial search space is [0..len-1] x [0..len-1] (full space)
 *
 * */
class Solution0 {
public:
    std::vector<int> twoSum(std::vector<int> &nums, int target) const {
        std::vector<int> index(nums.size());
        std::iota(index.begin(), index.end(), 0);
        std::sort(index.begin(), index.end(), [&](int i, int j) {
            return (nums[i] < nums[j]);
        });
        int i = 0, j = index.size() - 1;
        while(i < j) {
            int sum = nums[index[i]] + nums[index[j]];
            if(sum == target) {
                return {index[i], index[j]};
            } else if(sum < target) {
                ++i;
            } else {
                --j;
            }
        }
    }
};

/*
 * solution 1: use unordered_map
 * time complexity: O(n)
 *
 * */
class Solution1 {
public:
    std::vector<int> twoSum(const std::vector<int> &nums, int target) const {
        std::unordered_map<int, int> visited;
        for(int i = 0; i < nums.size(); ++i) {
            int residual = target - nums[i];
            if(visited.find(residual) != visited.end()) {
                return {visited.at(residual), i};
            } else {
                visited[nums[i]] = i;
            }
        }
    }
};

using Solution = Solution1;

int main() {
    Solution sln;
    std::vector<int> input{2, 7, 11, 15};
    int target = 9;

    auto result = sln.twoSum(input, target);
    std::cout << result[0] << "\t" << result[1] << std::endl;

    return 0;
}