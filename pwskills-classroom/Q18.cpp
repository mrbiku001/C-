// Q18. Count the number of triplets whose sum is equal to a given value x.
#include<iostream>
#include<vector>
using namespace std;
int tripletSum(vector<int> &v, int x){
    int count=0;
    for(int i=0; i<v.size(); i++){
        for(int j=i+1; j<v.size(); j++){
            for(int k=j+1; k<v.size(); k++){
                if(v[i]+v[j]+v[k]==x){
                count++;
                }
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
    cout<<"triplets available: "<<tripletSum(v,x);
    return 0;
}