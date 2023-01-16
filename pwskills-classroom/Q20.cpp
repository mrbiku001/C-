// Q20. Find the second largest value in a given array.
#include<iostream>
#include<vector>
using namespace std;
int secondLargest(vector<int> &v){
    int max=INT_MIN, secMax=INT_MIN;
    for(int i=0; i<v.size(); i++){
        if(v[i]>max){
            secMax=max;
            max=v[i];
        }
        else if(v[i]>secMax){
            secMax=v[i];
        }
    }
    return secMax;
}
int main(){
    vector<int> v={1,2,5,6,8,7,9};
    cout<<secondLargest(v);
    return 0;
}