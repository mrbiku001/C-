// Q2 - Given a vector arr[] sorted in increasing order of n size and an integer x, find if there exists a pair in the array whose sum is exactly x.(Easy)
//     Given: n>0
//     Input:[-1,0,1,2,3] x=2
//     Output:Yes
//     Input:[1,2,3,4] x=9
//     Output:No
#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> v={-1,0,1,2,3};
    int x, flag=0;
    cout<<"enter integer: ";
    cin>>x;
    for(int i=0; i<v.size(); i++){
        if(v[i]==x){
            flag=1;
            break;
        }
    }
    if(flag){
        cout<<"Yes";
    }
    else{
        cout<<"No";
    }
    return 0;
}