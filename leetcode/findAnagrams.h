//
// Created by jerry on 2024/8/24.
//
#include "headFile.h";
#ifndef LEETCODE_FINDANAGRAMS_H
#define LEETCODE_FINDANAGRAMS_H
enum { NUM = 128 };//effective c++第一章中提出的enum hack解法，这种方式可以尽可能的给你的预处理机制放假
struct Numsystem {

    enum system {
        negation,//不存在
        exist,//存在
        vanish,//消失
    }_System = negation;
    int _count = 0;//这里的count的作用就是记录我的重复的字符的个数
};
vector<int> findAnagrams(string s, string p)
{
    vector<Numsystem> aim;
    vector<int> target;
    aim.resize(129);
    for (auto& e : p) {
        aim[e]._System = Numsystem::exist;
        aim[e]._count++;
    }//将对应的位置通过harsh结构进行设置
    //    //这里有三种情况
    //    //1.当right遇见属于p字符串的话，right继续前进
    //    //2.当right遇见不属于p字符串的话，直接对当前的left和right的相对长度进行计算，将left进行移动，并且将其移动到right当前位置的下一个位置
    //    //3.当right遇见属于p字符串但是重复的字母的时候，左移left的位置，将left的位置移动到可以将right当前字母的位置进行覆盖
    //    //坑：我第一次做这个题时候，没有注意的就是p子串重可能出现重复的字母这使得我的第一次代码出现很大的错误
    int left = 0,right = 0,len = 0,size = p.size(),pos = 0;
    while(right < s.size()) {
        if(aim[s[right]]._System == Numsystem::exist) {
            if((--aim[s[right]]._count) == 0) aim[s[right]]._System = Numsystem::vanish;
            len = right - left + 1;
            if(len == size) target.push_back(left);
            right++;
        }
        else if(aim[s[right]]._System == Numsystem::vanish) {
            char tmp = s[right];
            while(s[left] != tmp) {
                aim[s[left]]._System = Numsystem::exist;
                aim[s[left]]._count++;
                left++;
            }
            left++;
            len = right - left + 1;
            if(len == size) target.push_back(left);
            right++;
        }
        else {
            while(left != right) {
                aim[s[left]]._count++;
                aim[s[left]]._System = Numsystem::exist;
                left++;
            }
            left++;
            right++;
        }
    }

    return target;
}
#endif //LEETCODE_FINDANAGRAMS_H
