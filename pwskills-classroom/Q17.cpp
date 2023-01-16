// Q17. Find the total number of pairs in the array whose sum is equal to the given value x.
#include<iostream>
#include<vector>
using namespace std;
int pairSum(vector<int> &v, int x){
    int count=0;
    for(int i=0; i<v.size(); i++){
        for(int j=i+1; j<v.size(); j++){
            if(v[i]+v[j]==x){
                count++;
            }
        }
    }
    return count;
}
int main(){
    vector<int> v={5,6,4,7,8,9,4};
    int x;
    cout<<"enter integer: ";
    cin>>x;
    cout<<"pairs available: "<<pairSum(v,x);
    return 0;
}