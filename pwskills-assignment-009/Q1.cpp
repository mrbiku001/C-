// Q1 - Given an integer array and two integers L and R. Find the sum of elements between the index L and index R.(Medium)
//     Note: Both L and R inclusive.
//     Input: [1,2,3,4,5] L=1 R=3
//     Output:9
//     Explanation:2+3+4=9
//     Input:[1,2,3,4,5] L=2 R=3
//     Output: 3
//     Explanation:3
#include<iostream>
#include<vector>
using namespace std;
void runningSum(vector<int> &v){
    for(int i=1; i<v.size(); i++){
        v[i]+=v[i-1];
    }
    return;
}
int main(){
    int size;
    cin>>size;
    vector<int> v(size);
    
    for(int i=0; i<size; i++){
        cin>>v[i];
    }
    runningSum(v);
    int L,R;
    cin>>L>>R;
    cout<<v[R]-v[L];
    return 0;
}