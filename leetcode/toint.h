//
// Created by jerry on 2024/8/24.
//
#include "headFile.h"
#ifndef LEETCODE_TOINT_H
#define LEETCODE_TOINT_H
int toint(const string& str)
{
    int sum = 0;
    for(auto e : str)
    {
        if(e != '+' && e != '-'){
            sum = sum * 10 + (int)(e - '0');
        }
    }
    if(str[0] == '-') return -sum;
    return sum;
}
string toString(int sum)
{
    bool flag = true;
    if(sum < 0) {
        sum = -sum;
        flag = false;
    }
    string str;
    int tmp = sum;
    while(tmp){
        str.push_back((char)((tmp % 10) + '0'));
        tmp /= 10;
    }
    int begin = 0, end = str.size() - 1;
    while(begin < end)
    {
        std::swap(str[begin],str[end]);
        begin++;
        end--;
    }
    if(flag == false) str.insert(str.begin(),'-');
    return str;
}

#endif //LEETCODE_TOINT_H
