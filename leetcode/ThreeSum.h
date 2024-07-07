//
// Created by jerry on 2024/7/7.
//

#ifndef THREESUM_H
#define THREESUM_H
class Solution {
public:
    //here are some changes
    int x = 0;
    vector<vector<int>> threeSum(vector<int>& nums) {
        std::sort(nums.begin(),nums.end(),less<int>());//using the standard sort to sort the Arrey
        vector<vector<int>> aim;
        int keyi = 0;
        while(keyi < nums.size())
        {
            int left = keyi + 1;
            int right = nums.size() - 1;
            while(left < right)
            {
                int ret = nums[keyi] + nums[left] + nums[right];
                if(ret == 0){
                    aim.push_back({nums[keyi],nums[left],nums[right]});
                    int prev_left = left;
                    while(left < right && nums[left] == nums[prev_left]){
                        left++;
                    }
                }
                else if(ret < 0){
                    int prev_left = left;
                    while(left < right && nums[left] == nums[prev_left]){
                        left++;
                    }
                }
                else {
                    int prev_right = right;
                    while(left < right && nums[right] == nums[prev_right])
                    {
                        --right;
                    }
                }
            }
            int prev_keyi = keyi;
            while(keyi < nums.size() && nums[keyi] == nums[prev_keyi])
            {
                keyi++;
            }
        }
        return aim;
    }
};
#endif //THREESUM_H
