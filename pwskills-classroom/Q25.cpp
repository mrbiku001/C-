// Q25. Given an integer array 'a' shorted in non-decreasing order, return an array of the squares of each number shorted in non-decreasing/increasing prder.
//     Input:[-10,-3,2,5,6]
//     Output:[4,9,25,36,100]
#include<bits/stdc++.h>
using namespace std;
void shortedSquareArray(vector<int> &v){
    vector<int> ans;
    int lft_ptr=0, rgt_ptr=v.size()-1;
    while(lft_ptr<=rgt_ptr){
        if(abs(v[lft_ptr])<abs(v[rgt_ptr])){
            ans.push_back(v[rgt_ptr]*v[rgt_ptr]);
            rgt_ptr--;
        }
        else{
            ans.push_back(v[lft_ptr]*v[lft_ptr]);
            lft_ptr++;
        }
    }
    reverse(ans.begin(), ans.end());
    for(int ele:ans){
        cout<<ele<<" ";
    }cout<<endl;
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
    shortedSquareArray(a);
    return 0;
}