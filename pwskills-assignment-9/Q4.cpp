// Q4 - ​Given an integer array arr, return the number of consecutive sequences(subarrays) with odd sum.(Hard)
//     Input:[1,3,5]
//     Output:4
//     Explanation:These sequences are [1],[3],[5] and [1,3,5]
//     Input:[0,2,4]
//     Output:0
#include<iostream>
using namespace std;
int main(){
    int arr[]={1,3,5};
    int n=sizeof(arr)/sizeof(arr[0]);
    int even=0, odd=0, count=0;
    for (int i=1; i<n; i++){
        arr[i]+=arr[i-1];
    }
    for(int i=0; i<n; i++){
        if(arr[i]%2){
            count+=even+1;
            //as itself as whole is a odd sum and odd-even is also odd
            odd++;
        }
        else{
            count+=odd;
            //here even-odd=odd
            even++;
        }
    }
    cout<<count;
    return 0;
}