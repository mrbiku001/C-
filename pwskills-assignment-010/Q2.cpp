// Q2 - You are given a n*n square matrix, you need to rotate the matrix by 90 degrees in clockwise direction. You need to do it in-place i.e. you are not allowed to make a new matrix and allocate the elements to it. Make the changes in the same matrix and print it.(Medium)
// n=3
// arr[] = {{1,2,3}, {4,5,6}, {7,8,9}}
// Output: {{7,4,1},{8,5,2},{9,6,3}}
//operation done first find transpose then swap diagonal elements
#include<iostream>
using namespace std;
int main(){
    //taking input matrix 
    int n;
    cin>>n;
    int arr[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin>>arr[i][j];
        }
    }
    //get transpose
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            swap(arr[i][j], arr[j][i]);
        }
    }
    //swap diagonal elements;
    for(int i=0; i<n; i++){
        for(int j=0; j<n/2; j++){
            swap(arr[i][j], arr[i][n-j-1]);
        }
    }
    //output
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<arr[i][j]<<" ";
        }cout<<endl;
    }
    return 0;
}