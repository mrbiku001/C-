// Q12. Find the last occurrence of an element x in a given array.
// Exp: traverse through the whole vector and compare the current element with the target element 'x' and if it maches then it will be out last seen index.
#include<iostream>
#include<vector>
using namespace std;
int solve(vector<int> &v, int x){
    int index=-1;
    for(int i=0; i<v.size(); i++){
        if(v[i]==x){
            index=i;
        }
    }
    return index;
}
int main(){
    vector<int> v={5,2,2,4,6,7};
    int x;
    cout<<"enter integer: ";
    cin>>x;
    cout<<"last occurance index : "<<solve(v,x);
    return 0;
}