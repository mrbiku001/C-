// Q26. Given an integer 'a', return the prefix sum/running sum in the same array without creating a new array.
//     Input:[5,4,1,2,3]
//     Output:[5,9,10,12,15]
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
    vector<int> a;
    int size;
    cin>>size;
    for(int i=0; i<size; i++){
        int ele; cin>>ele;
        a.push_back(ele);
    }
    runningSum(a);
    for(int ele:a){
        cout<<ele<<" ";
    }cout<<endl;
    return 0;
}