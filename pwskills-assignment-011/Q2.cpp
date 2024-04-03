// Q2. Given an array of intervals where intervals[i] = [start, end], merge all overlapping intervals, and create a function which returns a vector of the non-overlapping intervals that cover all the intervals in the input.(Hard)
//     Sample Input: arr[]=[[1,4],[2,3],[5,8],[6,9]] Sample Output: [[1,4],[5,9]]
//     Sample Input: arr[]=[[1,5],[3,9]] Sample Output: [1,9]
#include<bits/stdc++.h>
using namespace std;
vector<vector<int>> merge(vector<vector<int>>& s){
    sort(s.begin(), s.end());

    int n = s.size();
    vector<vector<int>> ans;
    for(int i=0; i<n; i++){
        if(ans.empty()){
            // if the ans vector is empty we have to push a value to compare
            ans.push_back(s[i]);
        }
        else{
            vector<int>&v = ans.back();
            // get the lase intervel pushed in ans
            int y= v[1]; //end time of previous interval
            //compare y with i's start time
            if(s[i][0]<=y){
                // i.e there is a overlap
                v[1]=max(y,s[i][1]);
            }
            //if it is not overlapping
            else{
                ans.push_back(s[i]);
            }
        }
    }
    return ans;
}

int main(){
    vector<vector<int>> mat={{1,4},{2,3},{4,5},{6,7}};
    vector<vector<int>> ans=merge(mat);
    for(int i=0; i<ans.size(); i++){
        cout<<ans[i][0]<<" "<<ans[i][1]<<endl;
    }
    return 0;
}