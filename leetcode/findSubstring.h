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
//try twice succssfully
vector<int> findSubstring2(string s, vector<string>& words) {
    vector<int> aim;

    int targetSize = words[0].size();
    int Sum = targetSize * words.size();
    for(int prev = 0,cur = 0;cur < targetSize;cur++,prev++){
        int begin = prev, end = cur;
        map<string,int> mstri;
        for(auto& e : words) { mstri[e]++; }
        while(end < s.size())
        {
            string tmp;
            if(end + targetSize > s.size()) tmp = string(s.begin() + end,s.end());
            else tmp = string(s.begin() + end,s.begin() + end + targetSize);
            if(mstri[tmp] >= 1) mstri[tmp]--;
            else{

                string ret;
                if(begin + targetSize > s.size()) ret = string(s.begin() + begin,s.end());
                else ret = string(s.begin() + begin,s.begin() + begin + targetSize);

                while(ret != tmp){
                    mstri[ret]++;
                    begin += targetSize;
                    if(begin + targetSize > s.size()) ret = string(s.begin() + begin,s.end());
                    else ret = string(s.begin() + begin,s.begin() + begin + targetSize);
                }
                begin += targetSize;
            }
            if(end - begin + targetSize == Sum) aim.push_back(begin);

            end += targetSize;
        }
    }
    return aim;

}
vector<int> findSubstring3(string s,vector<string>& words)
{
    vector<int> ret;
    unordered_map<string,int> hash1;
    for(auto& e : words) hash1[e]++;
    int len = words[0].size() , m = words.size();
    for(int i = 0;i < len;i++){
        unordered_map<string,int> hash2;
        for(int left = i,right = i,count = 0;right + len <= s.size();right += len){
            string in = s.substr(right,len);
            hash2[in]++;
            if(hash1.count(in) && hash2[in] <= hash1[in]) count++;
            if(right - left + len > len * m) {//出窗口
                string out = s.substr(left,len);
                if((hash2[out]--) <= hash1[out]) count--;
                left+=len;
            }
            if(count == m) ret.push_back(left);
        }
    }
    return ret;
}
void test()
{
    string src = "aaaaaaaaaaaaaa";
    vector<string> vstr({"aa","aa"});
    vector<int> arr = findSubstring2(src,vstr);
}

#endif //LEETCODE_FINDSUBSTRING_H
