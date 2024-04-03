// Q3 - Given a vector arr[] sorted in increasing order of n size and an integer x, find if there exists a pair in the array whose absolute difference is exactly x.(Medium)
//     Given: n>0
//     Input:[5,10,15,20,26] x= 10
//     Output:Yes
//     Input:[5,6,7,8,9] x=4
//     Output:Yes
//     Input:[9,23,45,69,78] x=56
//     Output:No
#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> v={5,10,15,20,26};
    int x,flag=0;
    cout<<"enter integer: ";
    cin>>x;
    for(int i=0; i<v.size(); i++){
        for(int j=i+1;j<v.size(); j++){
            if((v[i]-v[j]==x)||v[j]-v[i]==x){
                flag=1;
                break;
            }
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