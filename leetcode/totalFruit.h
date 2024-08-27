//
// Created by jerry on 2024/8/27.
//
#include "headFile.h"
#ifndef LEETCODE_TOTALFRUIT_H
#define LEETCODE_TOTALFRUIT_H
int totalFruit(vector<int>& fruits) {
    pair<int,int> lhs,rhs;//first表示的是水果的种类,second 表示的是水果的数量
    rhs.first = -1,rhs.second = 0;
    lhs.first = -1,lhs.second = 0;
    int ret = -INT_MAX;
    for(int left = 0,right = 0;right < fruits.size();right++){
        if(lhs.first == fruits[right] || rhs.first == fruits[right]){
            if(lhs.first == fruits[right]) lhs.second++;
            else rhs.second++;
        }else if(lhs.first == -1 || rhs.first == -1){//有空位
            if(lhs.first == -1){
                lhs.first = fruits[right];
                lhs.second++;
            }else {
                rhs.first = fruits[right];
                rhs.second++;
            }
        }else{//这种时候就是出现问题需要出窗口
            while(lhs.second != 0 && rhs.second != 0)
            {
                if(fruits[left] == lhs.first) lhs.second--;
                else rhs.second--;
                left++;
            }
            if(lhs.second == 0) {
                lhs.second = 1;
                lhs.first = fruits[right];
            }else {
                rhs.second = 1;
                rhs.first = fruits[right];
            }
        }
        //更新结果
        ret = std::max(ret,lhs.second + rhs.second);
    }
    return ret;
}
void test()
{
    vector<int> arr = {1,2,3,2,2};
    int ret = totalFruit(arr);
    cout << ret << endl;
}

#endif //LEETCODE_TOTALFRUIT_H
