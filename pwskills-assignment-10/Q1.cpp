// Q1 - Given a 2D matrix with m rows and n columns containing integers, find and print the maximum value present in the array.(Easy)
//     m=3
//     n=3
//     arr[] = {{1,2,3}, {4,5,6}, {7,8,9}}
//     Output: 9
#include<iostream>
using namespace std;
int main(){
    //m,n order of matrix
    int m, n;
    cin>>m>>n;
    int arr[m][n];
    //taking input
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cin>>arr[i][j];
        }
    }

    //traversing and updating max
    int max=INT_MIN;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(max<arr[i][j]) max=arr[i][j];
        }
    }

    cout<<max;
    return 0;
}