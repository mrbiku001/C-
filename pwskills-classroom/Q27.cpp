// Q27. Check if we can partion an input array into two subarrays with equal sum. More formally, check that the prefix sum of a part of the array is equal to the suffix sum of the rest of the array.
//     Input:[5,2,3,4]
//     Output:True
#include<iostream>
#include<vector>
using namespace std;
bool check(vector<int> &v){
    int total_sum=0;
    for(int i=0; i<v.size(); i++){
        total_sum+=v[i];
    }
    int prefix_sum=0;
    for(int i=0; i<v.size(); i++){
        prefix_sum+=v[i];
        int suffix_sum=total_sum-prefix_sum;
        if(prefix_sum==suffix_sum){
            return true;
        }
    }
    return false;
}
int main(){
    vector<int> a;
    int size;
    cin>>size;
    for(int i=0; i<size; i++){
        int ele; cin>>ele;
        a.push_back(ele);
    }
    cout<<check(a)<<endl;
    return 0 ;
}