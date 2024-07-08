//
// Created by jerry on 2024/7/7.//双指针

#ifndef THREESUM_H
#define THREESUM_H
//三数之和
    vector<vector<int>> threeSum(vector<int>& nums) {//
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
//四叔之和
void setThreeNum(vector<vector<int>>& aim,int target,vector<int>& nums,int end)
    {
        int keyi = 0;
        while(keyi < end - 1)
        {
            int left = keyi + 1;
            int right = end;
            long long int firs,scon,thir;
            while(left < right)
            {
                firs = nums[left],scon = nums[right],thir = nums[keyi];
                long long int ret = firs + scon + thir;//这个地方时值得注意和吐槽的点，因为如果这里ret用int的话，当数过大会使得ret超出范围
                if(ret == target){
                    aim.push_back({nums[keyi],nums[left],nums[right],nums[end+1]});
                    int prev_left = left;
                    while(left < right && nums[left] == nums[prev_left]){
                        left++;
                    }
                }
                else if(ret < target){
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
            while(keyi < end - 1 && nums[keyi] == nums[prev_keyi])
            {
                keyi++;
            }
        }
    }//这里的原理就是和三数之和的原理基本类似
vector<vector<int>> fourSum(vector<int>& nums, int target) {
        std::sort(nums.begin(),nums.end(),less<int>());
        vector<vector<int>> aim;
        int size = nums.size();
        int end = size - 1;
        while(end >= 3)
        {
            setThreeNum(aim,target - nums[end],nums,end-1);
            int prev_end = end;
            while(end >= 3 && nums[end] == nums[prev_end]){
                end--;
            }//为了避免重复，跳过重复的数字
        }
        return aim;
    }
#endif //THREESUM_H
