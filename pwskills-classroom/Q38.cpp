// Q38. Print the max value of the array.
#include <iostream>
using namespace std;
int rF(int *arr, int idx, int n)
{
    if (idx == n - 1)
        return arr[idx];
    return max(arr[idx], rF(arr, idx + 1, n));
}
int main()
{
    int arr[] = {3, 10, 3, 2, 5};
    cout << rF(arr, 0, 5);
    return 0;
}