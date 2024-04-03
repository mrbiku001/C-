// Q6 - Given a vector array nums, print the count of triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == x. Where k is an integer given by the user.(Hard)
//     Note: The solution set must not contain duplicate triplets and should not have 3 loops.
//     Input:[-1,0,1,2,-1,-4] x=0
//     Output:3
//     Explanation:The two triplets are: -1,0,1 and 1,2,-1
//     Input:[1,2,3] x=5
//     Output:0
#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> v={-1,0,1,2,-1,-4};
    int x,count=0;
    cout<<"enter integer: ";
    cin>>x;
    for(int i=0; i<v.size(); i++){
        for(int j=i+1;j<v.size(); j++){
            for(int k=j+1; k<v.size(); k++){
                if(v[i]+v[j]+v[k]==x){
                    count++;
                }
            }
        }
    }
    cout<<count;
    return 0;
}