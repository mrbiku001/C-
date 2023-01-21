// Q3 - ​Given an integer array arr consisting of 0’s and 1’s only, return the max length of sequence which contains equal numbers of 0 and 1.(Medium)
//     Input:arr=[0,1,0,1]
//     Output:4
//     Explanation:The longest sequence is 0,1,0,1
//     Input:arr=[0,1,1,0,1,1,1]
//     Output:4
//     Explanation:The longest sequence is 0,1,1,0
#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> arr;
    int size, length;
    cin>>size;
    for(int i=0; i<size; i++){
        int ele; cin>>ele;
        arr.push_back(ele);
    }
    int track=0;
    for(int i=0; i<size; i++){
        if(arr[i]){
            track++;
        }
        else{
            track--;
        }
        if(track==0){
            length=i+1;
        }
    }
    cout<<"max length = "<<length;
    return 0;
}