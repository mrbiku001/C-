// Q37. Given an array print all the elements of the array recursively.
#include <iostream>
using namespace std;
void rF(int *arr, int idx, int n)
{
    // basecase
    if (idx == n) return;
    // selfwork
    cout << arr[idx] << endl;
    // assum
    rF(arr, idx + 1, n);
}
int main() 
{
    int n = 5;
    int arr[] = {6, 1, 9, 3, 4};
    rF(arr, 0, n);

    return 0;
}