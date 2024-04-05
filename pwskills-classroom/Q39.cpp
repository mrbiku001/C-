// Q39. Print the sum value of the elements in array.
#include <iostream>
using namespace std;
int rF(int *arr, int idx, int n)
{
    if (idx == n - 1)
        return arr[idx];
    return arr[idx] + rF(arr, idx + 1, n);
}
int main()
{
    int arr[] = {2, 3, 5, 20, 1};
    int n = 5;
    cout << rF(arr, 0, 5);
    return 0;
}