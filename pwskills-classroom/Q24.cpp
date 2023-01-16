// Q24. Given an array of integer 'a', move all the even integers at the begnning of the array followed by all the odd integers. The relative order of odd or even integer does not matter. Return any array that satisfies the condition.
#include<iostream>
#include<vector>
using namespace std;
void shortOddAndEven(vector<int> &v){
    int lft_ptr=0, rgt_ptr=v.size()-1;
    while(lft_ptr<rgt_ptr){
        if(v[lft_ptr]%2==1 && v[rgt_ptr]%2==0){
            swap(v[lft_ptr], v[rgt_ptr]);
            lft_ptr++, rgt_ptr--;
        }
        if(v[lft_ptr]%2==0) lft_ptr++;
        if(v[rgt_ptr]%2==1) rgt_ptr--;
    }
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
    shortOddAndEven(a);
    for(int i=0; i<size; i++){
        cout<<a[i]<<" ";
    }cout<<endl;
    return 0;
}