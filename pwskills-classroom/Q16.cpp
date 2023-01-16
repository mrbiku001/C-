// Q16. Find the difference between the sum of elements at even indices to the sum of elements at off indices.
#include<iostream>
#include<vector>
using namespace std;
int solve(vector<int> &v){
    int sum=0;
    for(int i=0; i<v.size(); i++){
        if(i%2){
            sum-=v[i];
        }
        else{
            sum+=v[i];
        }
    }
    return sum;
}
int main(){
    vector<int> v={5,6,4,8,6,9};
    cout<<solve(v);
    return 0;
}