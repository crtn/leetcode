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
 * for current search space [i..j] x [i..j], i < j:
 *   if nums[i] + nums[j] < target, then we can exclude [i] x [i..j]
 *      because nums[i] + nums[t] <= nums[i] + nums[j] < target for any t <- [i..j],
 *      so the new search space become [i+1..j] x [i..j], because i < j, it is
 *      [i+1..j] x [i+1..j]
 *   if nums[i] + nums[j] > target, then we can exclude [i..j] x [j]
 *      because nums[t] + nums[j] >= nums[i] + nums[j] > target for any t <- [i..j],
 *      so the new search space become [i..j] x [i..j-1], because i < j, it is
 *      [i..j-1] x [i..j-1]
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