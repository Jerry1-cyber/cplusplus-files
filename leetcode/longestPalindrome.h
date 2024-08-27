//
// Created by jerry on 2024/8/24.
//
#include "headFile.h";
#ifndef LEETCODE_LONGESTPALINDROME_H
#define LEETCODE_LONGESTPALINDROME_H
string longestPalindrome(string s) {
    string ret;
    if(s.size() == 1) return s;
    if(s.size() == 2) return (s[0] == s[1] ? s : (ret += s[0]));
    int cur = 1;
    int size = s.size();
    int len = 1;
    int rem_left = 0,rem_right = 0;

    //这道题的基本思路还是双指针的思想
    //1.可能是bab类型的回文数
    //2.可能是baab类型的回文数
    //因此这里我们应该应该对两种情况分别进行讨论
    //>=0 和 <= s.size()这两个条件时至关重要的对于边界来说的话
    while(cur < size)
    {
        int left1 = cur - 2,left2 = cur - 1,right = cur;
        if(s[cur] == s[left2])
        {
            while(right < s.size() && left2 >= 0 && s[left2] == s[right])
            {
                left2--;
                right++;
            }
            if(len < right - left2 - 1) {
                len = right - left2 - 1;
                rem_left = left2 + 1;
                rem_right = right - 1;
            }
        }
        right = cur;
        if(left1 >= 0 && s[cur] == s[left1]){
            while(right < s.size() && left1 >= 0 && s[left1] == s[right]){
                left1--;
                right++;
            }
            if(len < right - left1 - 1){
                len = right - left1 - 1;
                rem_left = left1 + 1;
                rem_right = right - 1;

            }
        }
        cur++;
    }
    while(rem_left <= rem_right)
    {
        ret.push_back(s[rem_left]);
        rem_left++;
    }
    return ret;
}
#endif //LEETCODE_LONGESTPALINDROME_H
