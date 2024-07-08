#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <algorithm>
#include "twoPtr.h"
int main()
{
    vector<int> arr = {1000000000,1000000000,1000000000,1000000000};
    vector<vector<int>> ret = fourSum(arr,0);
    return 0;
}
