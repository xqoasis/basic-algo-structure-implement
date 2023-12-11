#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int partition(vector<int> &nums, int lo, int hi){
    int pivot = nums[lo];
    int i = lo + 1;
    int j = hi;
    while (i <= j){
        while (i < hi && nums[i] <= pivot){
            i ++;
        }
        while (j > lo && nums[j] > pivot){
            j --;
        }
        if (i >= j){
          break;
        }
        // i >= j, a[j] <= pivot
        // nums[i] > pivot, nums[j] <= pivot
        swap(nums[i], nums[j]);
    }
    swap(nums[lo], nums[j]);
    //nums[i] <= pivot, nums[j] > pivot
    return j;
}

void sort(vector<int> &nums, int lo, int hi){
    if (lo >= hi){
        return;
    }
    int p = partition(nums, lo, hi);
    sort(nums, lo, p - 1);
    sort(nums, p + 1, hi);
}



int main(){
    vector<int> input = {2, 4, 3, 7,6, 9, 1};
    sort(input, 0, input.size()- 1);
    for (auto i : input){
        cout << i << " ";
    }
    return 0;
}
