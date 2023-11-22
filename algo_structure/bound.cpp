#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
// #include <iostream>
// #include <algorithm>
// #include <vector>

// using namespace std;

// int main(){
//     int num;
//     cout << "input the num" << endl;

//     while (cin >> num){
//         int arr[num];
//         for (int i = 0; i < num; ++i){
//             cin >> arr[i];
//         }

//         cout << "从qiandaohou查找,第一个不小于10的是";

//         if ((lower_bound(arr, arr+num, 10) - arr) == num){
//             cout << endl;
//             cout << "没有大于10的" << num;
//         }else{
//             cout << arr[lower_bound(arr, arr+num, 10) - arr] << endl;
//         }
//     }

//     return 0;

// }


// C++ Program to count pairs
// whose sum divisible by 'K'

 
// Program to count pairs whose sum divisible
// by 'K'
int countKdivPairs(vector<int> A, int n, int K)
{
    // Create a frequency array to count
    // occurrences of all remainders when
    // divided by K
    unordered_map freq;
 
    // Count occurrences of all remainders
    for (auto a:A)
        freq[a % K] ++ ; // freq[remainder] = occurences
 
    // If both pairs are divisible by 'K'
    int sum = freq[0] * (freq[0] - 1) / 2;
 
    // count for all i and (k-i)
    // freq pairs
    for (int i = 1; i <= K / 2 && i != (K - i); i++)
        sum += freq[i] * freq[K - i];
    // If K is even
    if (K % 2 == 0)
        sum += (freq[K / 2] * (freq[K / 2] - 1) / 2);
    return sum;
}
 
// Driver code
int main()
{
 
    int A[] = { 2, 2, 1, 7, 5, 3 };
    int n = sizeof(A) / sizeof(A[0]);
    int K = 4;
    cout << countKdivPairs(A, n, K);
 
    return 0;
}