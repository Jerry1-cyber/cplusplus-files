//
// Created by jerry on 2024/8/27.
//
#include "headFile.h"
#ifndef LEETCODE_FINDSUBSTRING_H
#define LEETCODE_FINDSUBSTRING_H
//firstly try - 2024 - 8 - 27
vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> aim;
    map<string,int> mstri;
    for(auto& e : words) { mstri[e]++; }
    int targetSize = words[0].size();
    int Sum = targetSize * words.size();
    int begin = 0 , end = 0;
    while(end < s.size())
    {
        string tmp(s.begin() + end, s.begin() + end + targetSize);
        if(mstri[tmp] >= 1) mstri[tmp]--;
        else{
            string ret(s.begin() + begin,s.begin() + begin + targetSize);
            while(ret != tmp){
                mstri[ret]++;
                begin += targetSize;
                ret = string(s.begin() + begin,s.begin() + begin + targetSize);
            }
            begin += targetSize;
        }
        if(end - begin + targetSize == Sum) aim.push_back(begin);
        end += targetSize;
    }
    return aim;
}
void test()
{
    string src = "wordgoodgoodgoodbestword";
    vector<string> vstr({"word","good","best","good"});
    vector<int> arr = findSubstring(src,vstr);
}

#endif //LEETCODE_FINDSUBSTRING_H
