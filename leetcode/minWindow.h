//
// Created by jerry on 2024/8/27.
//
#include "headFile.h"
#ifndef LEETCODE_MINWINDOW_H
#define LEETCODE_MINWINDOW_H
string minWindow(string s, string t) {
    unordered_map<char,int> hash1;
    for(auto e : t)
        hash1[e]++;

    pair<int,int> ret = make_pair(-1,INT_MAX);//begin and size
    unordered_map<char,int> hash2;
    for(int left = 0,right = 0,count = 0;right < s.size();right++){

        //进入窗口
        hash2[s[right]]++;
        if(hash2[s[right]] <= hash1[s[right]]) count++;//有效的字符++进入窗口
        //保证s[left] 属于 t
        while(hash2[s[left]] > hash1[s[left]] && left < right){
            hash2[s[left]]--;
            left++;
        }
        if(count == t.size()) {
            if(right - left + 1 < ret.second) {
                ret.first = left;
                ret.second = right - left + 1;
            }
            left++;
        }
    }
    if(ret.first == -1) return "";
    else return s.substr(ret.first,ret.second);
}
string minWindow2(string s, string t) {
    int hash1[128] = { 0 };
    for(auto e : t)
        hash1[e]++;
    int hash2[128] = { 0 };//hash2用于和hash1作对比
    int len = t.size(), Min = INT_MAX , begin = -1;
    cout << len << endl;
    for(int left = 0,right = 0,count = 0;right < s.size();right++){
        hash2[right]++;//进窗口
        if(hash2[right] <= hash1[right]) count++;//有效的进窗口
        while(count > len || hash2[left] > hash1[left])//count多了需要出窗口,保证left的位置是有效的
            if(hash2[left]-- <= hash1[left]) count--;
        if(count == len && Min > right - left + 1){
            Min = right - left + 1;
            begin = left;
        }
        cout << count << endl;
        cout << s.substr(left,right - left + 1) << endl;
    }
    if(Min == INT_MAX) return "";
    else return s.substr(begin,Min);
}
void test()
{
    string ret = minWindow2("ADOBECODEBANC","ABC");
    cout << ret;
}

#endif //LEETCODE_MINWINDOW_H
