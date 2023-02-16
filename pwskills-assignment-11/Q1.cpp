// Q1. Given a m*n matrix, Write a function which returns true if the matrix is a perfect matrix. A matrix is called perfect if every diagonal from top-left to bottom-right has the same elements. (Easy)
//     Sample Input: arr[]=[[9,8,7,6],[5,9,8,7],[1,5,9,8]]
    
//     9 8 7 6
//     5 9 8 7
//     1 5 9 8
    
//     Sample Output: true
#include<iostream>
using namespace std;
int main(){
    int m,n;
    cin>>m>>n;

    int arr[m][n];
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cin>>arr[i][j];
        }
    }

    bool flag=true;
    for(int i=0; i<m-1; i++){
        for(int j=0; j<n-1; j++){
            if(arr[i][j]!=arr[i+1][j+1]){
                flag=false;
                break;
            }
        }
    }

    if(flag){
        cout<<"matrix is proper";
    }
    else{
        cout<<"matrix is not proper";
    }
    return 0;
}