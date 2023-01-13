// Q6 - Given an integer array containing n elements. Find the element in the array for which all the elements to its left are smaller than it and all the elements to the right of it are larger than it. Here 1<n<101.
//     Ex: arr=[1,6,5,7,10,8,9] Output: 7
//     Explanation: Here all the elements to the left of 7 are smaller than it and all the elements to the right of it are greater than it.
//     Ex: arr=[5,6,2,8,10,9] Output: -1
//     Explanation: Here there is no element in the array which satisfies the given condition.
#include<iostream>
using namespace std;
int maxLeft(int a[],int n,int i){
    int max=INT_MIN;
    for(int j=i-1; j>=0; j--){
        if(a[j]>max) max=a[j];
    }
    return max;
}
int minRight(int a[],int n,int i){
    int min=INT_MAX;
    for(int j=i+1; j<n-1; j++){
        if(a[j]<min) min=a[j];
    }
    return min;
}
int main(){
    int arr[]={5,6,2,8,10,9};
    int n=sizeof(arr)/sizeof(arr[0]);
    for(int i=1; i<n-1; i++){
        if((arr[i]>maxLeft(arr,n,i))&&(arr[i]<minRight(arr,n,i))){
            cout<<arr[i];
            return 0;
        }
    }
    cout<<"no such element found";
    return 0;
}