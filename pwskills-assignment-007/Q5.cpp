// Q5 - Given an array containing n distinct integers in the range [0,n] (inclusive of both 0 and n) (inclusive of both 0 and n). Find and return the only number of the range that is not present in the array. Here 1<n<101.
//     Ex: arr=[3,0,1] Output: 2
//     n=3, thus the range will be [0,3]
//     Ex: arr=[8,6,4,2,3,5,0,1] Output: 7
//     n=8, thus the range will be [0,8]
#include<iostream>
using namespace std;
int main(){
    int a[]={8,6,4,2,3,5,0,1};
    int n=sizeof(a)/sizeof(a[0]);
    int sum, rangeSum=n*(n+1)/2;
    for(int i=0; i<n; i++){
        sum+=a[i];           
    }
    cout<<"missing number = "<<rangeSum-sum;
    return 0;
}