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
//四数之和
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
//滑动窗口，同向双指针，因此这里会有变化
int minSubArrayLen(int target, vector<int>& nums) {
        int left = 0;
        int right = 0;
        int size = nums.size();
        int sum = 0;
        int gap = 0;
        bool flag = false;
        while(right < size)
        {
            while(sum < target && right < size)
            {
                sum+=nums[right++];
            }
            if(sum >= target && flag == false) {
                flag = true;
                gap = right - left;
            }
            else if(sum >= target && flag == true) {
                if(gap > right - left) gap = right - left;
            }
            sum-=nums[left++];
        }
        return gap;
    }
//无重复字符的最长子串，滑动窗口

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
//438，滑动窗口，找到所有的异位词
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
#endif //THREESUM_H
