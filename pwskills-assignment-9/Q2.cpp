// Q2 - ​There is a man going on a trek. The trek consists of n + 1 points at different altitudes. The man starts his trek on point 0 with altitude equal 0.You are given an integer array height of length n where height[i] is the net height in altitude between points i​ and i + 1 for all (0 <= i < n). Return the highest altitude of a point.(Easy)
//     Input:height=[-4,1,6,0,-8]
//     Output:3
//     Explanation:The man starts at 0 and since then the altitudes covered will be [0, 4, 3,3,3, 5] so the greatest altitude will be 3
//     Input:height=[ 5, 3, 2]
//     Output:0
//     Explanation:The man starts at 0 and since then the altitudes will be[0, 5, 3, 2] so the greatest altitude will be 0.
#include<iostream>
#include<vector>
using namespace std;
void heightOfTrek(vector<int> &heights){
    for(int i=0; i<heights.size()-1; i++){
        heights[i+1]+=heights[i];
    }
    return;
}
int heighestAltitude(vector<int> &heights){
    int heighestAlt=INT_MIN;
    for(int i=0; i<heights.size(); i++){
        if(heighestAlt<heights[i]) heighestAlt=heights[i];
    }
    return heighestAlt;
}
int main(){
    int points; //no. of altitudes
    cout<<"enter no. of altitudes where 0 is one of them: ";
    cin>>points;
    vector<int> heights(points,0); //is the net height in altitude between points i and i+1
    for(int i=1; i<points; i++){
        int ele; cin>>ele;
        heights[i]=ele;
    } 
    heightOfTrek(heights); //makes values of height=height of treks
    cout<<heighestAltitude(heights);
    return 0;
} 