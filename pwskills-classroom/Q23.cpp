// Q23. Short an array containing only 0's and 1's.
// intput: 1 0 1 0 1
// output: 0 0 1 1 1
#include<iostream>
#include<vector>
using namespace std;
//in the below code we need to traverse the array two times
/* void shortZerosAndOne(vector<int> &v){
        int zero_count=0;
        for(int ele:v){
            if(ele==0){
                zero_count++;
            }
        }
        for(int i=0; i<v.size(); i++){
            if(i<zero_count){
                v[i]=0;
            }
            else{
                v[i]=1;
            }
        }
        return;
    } */
void shortZerosAndOne(vector<int> &v){
    int i=0, j=v.size()-1;
    while(i<j){
        if(v[i]==1 && v[j]==0){
            v[i++]=0;
            v[j--]=1;
        }
        if(v[i]==0) i++;
        if(v[j]==1) j--;
    }
    return;
}
int main(){
    vector<int> v;
    int size;
    cin>>size;
    for(int i=0; i<size; i++){
        int ele; cin>>ele;
        v.push_back(ele);
    }
    shortZerosAndOne(v);
    for(int i=0; i<size; i++){
        cout<<v[i]<<" ";
    }cout<<endl;
    return 0;
}
