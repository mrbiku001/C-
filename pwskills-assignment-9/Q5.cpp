// Q5 - Given an integer array arr, return an array ans such that ans[i] is equal to the product of all the elements of arr except arr[i].(Hard)
//     Input: arr=[1,3,5,7]
//     Output: [105,35,21,15]
//     Explanation: ans=[3*5*7,1*5*7,1*3*7,1*3*5]
//     Input: [-5,-4,0,4,5]
//     Output: [0,0,400,0,0]
#include<iostream>
using namespace std;
int main(){
    int arr[]={1,3,5,7};
    int n=sizeof(arr)/sizeof(arr[0]);
    int ans[n];
    for(int i=0; i<n; i++){
        ans[i]=1;
        for(int j=0; j<n; j++){
            if(i==j){
                continue;;
            }
            else{
                ans[i]*=arr[j];
            }
        }
    }

    for(int i=0; i<n; i++){
        cout<<ans[i]<<" ";
    }
    return 0;
}