// Q1 - Given an integer array(arr) and its size(n), print the count of odd and even integers present in the array. 
//     For ex: arr[]={1,2,3,4,5} n=5 
//     Output: Odd Numbers = 3 Even Numbers = 2
//     Explanation: The even numbers present in the array are 2,4 and the odd numbers present in the array
//     are 1,3 and 5.
#include<iostream>
using namespace std;
int evennum(int array[], int size){
    int count=0;
    for(int i=0; i<size; i++){
        if(!(array[i]%2)) count++; 
    }
    return count;
}
int oddnum(int array[], int size){
    int count=0;
    for(int i=0; i<size; i++){
        if(array[i]%2) count++; 
    }
    return count;
}
int main(){
    int a[]={1,2,3,4,5};
    int n=sizeof(a)/sizeof(a[0]);
    cout<<"odd number = "<<oddnum(a,n)<<endl;
    cout<<"even number = "<<evennum(a,n);
}