//
// Created by jerry on 2024/8/26.
//
#include "headFile.h"
#ifndef LEETCODE_MINOPERATIONS_H
#define LEETCODE_MINOPERATIONS_H
int minOperations(vector<int>& nums, int x) {
    int left = 0, right = nums.size() - 1;
    int Min = INT_MAX;
    int target = x;
    while(right >= 0 && target >= 0){
        target -= nums[right--];
    }
    if(right < 0 && target >= 0) return -1;//无论怎样都不能搬到
    if(right < 0 && target == 0) return nums.size();
    while(right < nums.size())
    {
        target += nums[++right];//进入窗口
        while(target > 0 && left < right)
            target -= nums[left++];
        int tmp = left - 0 + nums.size() - 1 - right;
        if(target == 0) Min = std::min(Min,tmp);
    }
    if(Min == INT_MAX) Min = -1;
    return Min;
}
int minOperations2(vector<int>& nums, int x) {
        int left = 0, right = nums.size() - 1;
        while(right >= 0 && x >= 0){
            x -= nums[right--];
        }
        if(x > 0) return -1;
        else if(x == 0) return nums.size();
        //这个时候x < 0
        int Min = INT_MAX;
        for(;right < nums.size();right++){
            x += nums[++right];
            if(x > 0) {
                while(x > 0 && left < right)
                    x -= nums[left++];
            }
            if(x == 0){
                int tmp = left + nums.size() - 1 - right;
                Min = std::min(Min,tmp);
            }

        }
        if(Min == INT_MAX) Min = -1;
        return Min;
    }
int minOperations3(vector<int>& nums, int x) {
    int Sum = 0;
    for(auto e : nums)
        Sum += e;
    int target = Sum - x;//原问题等价于求最长的和为target的数组
    int curSum = 0;
    int max = -INT_MAX;
    for(int left = 0,right = 0;right < nums.size();right++)
    {
        curSum += nums[right];//进入窗口
        if(curSum > target) {
            while(curSum > target)
                curSum -= nums[left++];
        }//出窗口
        if(curSum == target) max = std::max(max,right - left + 1);
    }
    if(max == -INT_MAX) return -1;
    return nums.size() - max;
}
void test()
{
    vector<int> arr = {5,5,5};
    int ret = minOperations3(arr,3);
    cout << ret << endl;
}

#endif //LEETCODE_MINOPERATIONS_H
