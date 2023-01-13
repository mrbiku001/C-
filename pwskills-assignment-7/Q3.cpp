// Q3 - Given an integer array and its size, reverse the array and print it . Here 1<size<101 .
//     For ex: arr[]={1,2,3,4,5} n=5 
//     Output: 5,4,3,2,1
//     arr[]={1,1,1,1,1] n=5
//     Output: 1,1,1,1,1
#include<iostream>
using namespace std;
void revArray(int array[], int size){
    int start=0;
    int end=size-1;
    while(start<end){
        int temp=array[start];
        array[start]=array[end];
        array[end]=temp;
        start++,end--;
    }
    for(int i=0; i<size; i++){
        cout<<array[i]<<" ";
    }
}
int main(){
    int a[]={1,2,3,4,5};
    int n=sizeof(a)/sizeof(a[0]);
    revArray(a,n);
    return 0;
}