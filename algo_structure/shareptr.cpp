#include <mutex>
#include <iostream>
using namespace std;

vector<int> quickS(vector<int> &a, int l, int r) {
    if (l >= r) return;
    int p = partition(a, l, r);
    quickS(a, l, p - 1);
    quickS(a, p+1, r);
    return;

}
int partition(vector<int> &a, int l,int r) {

    int pivot = a[l];
    int i = l + 1, j = r;
    while (i <= j) {
        while (i < r && a[i] <= pivot) i ++;
        while (j > l && a[j] > pivot) j --;
        //
        if (i >= j) break;
        swap(a[i], a[j]);
    }
    // i >= j, a[j] <= pivot
    swap(a[l], a[j]);
    return j;
}


int main() {
    vector<int> input = {2, 4, 3, 7,6, 9, 1};
    quickS(input, 0, input.size()- 1);
    for (auto i : input){
        cout << i << " ";
    }
    return 0;
}
