//
// Created by jerry on 2024/8/24.
//
#include "headFile.h"
#ifndef LEETCODE_LENGTHOFLONGESTSUBSTRING_H
#define LEETCODE_LENGTHOFLONGESTSUBSTRING_H
int lengthOfLongestSubstring(string s) {
    if(s == string(" ")) return 1;
    vector<bool> alphabet;
    alphabet.resize(129);
    for(size_t i = 0;i < 130;i++){
        alphabet[i] = false;
    }
    int size = s.size();
    int left = 0,right = 0,len = 0;
    for(;right < size;right++)
    {
        if(alphabet[s[right]] == false){
            alphabet[s[right]] = true;
            len = max(len,right - left + 1);
        }
        else{
            char tmp = s[right];
            while(s[left] != tmp) {
                alphabet[s[left++]] = false;
            }
            left++;
        }
    }
    return len;
}
#endif //LEETCODE_LENGTHOFLONGESTSUBSTRING_H
