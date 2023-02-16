// Q3. Given an array of intervals where arr[i] = [start, end], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
//     Sample Input: arr[]=[[1,4],[2,3],[4,5],[6,7]] Sample Output: 2
//     Explanation: The interval 1,4 and 2,3 are overlapping so removing any one of them will make the intervals non overlapping.
//     Sample Input: arr[]=[[1,2],[2,3],[3,4],[4,5]]
//     Sample Output: 0
#include<bits/stdc++.h>
using namespace std;
int num(vector<vector<int>>& s){
    sort(s.begin(), s.end());

   int n = s.size(), count=0;
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
                count++;
            }
            //if it is not overlapping
            else{
                ans.push_back(s[i]);
            }
        }
    }
    return count;
}

int main(){
    vector<vector<int>> mat={{1,4},{2,3},{4,5},{6,7}};
    int ans=num(mat);
    cout<<ans;
    return 0;
}