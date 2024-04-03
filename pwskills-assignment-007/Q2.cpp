// Q2 - Given an integer array and its size, find the sum of the greatest and the smallest integer present in the array. 
//     Here 1< size <101 
//     For ex: arr[]={1,2,3,4,5} n=5 
//     Output: 6 
//     Explanation: The smallest number in the array is 1 and the greatest numbers in the array is 5, so the sum
//     will be 1+5=6
#include<iostream>
using namespace std;
int arrayMax(int array[], int size){
    int max=INT_MIN;
    for(int i=0; i<size; i++){
        if(array[i]>max) max=array[i];
    }
    return max;
}
int arrayMin(int array[], int size){
    int min=INT_MAX;
    for(int i=0; i<size; i++){
        if(array[i]<min) min=array[i];
    }
    return min;
}
int main(){
    int a[]={1,2,3,4,5}, n=sizeof(a)/sizeof(a[0]);
    cout<<"Max and min sum = "<<arrayMax(a,n)+arrayMin(a,n)<<endl;
    return 0;
}