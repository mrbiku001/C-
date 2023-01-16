// Q19. Find the unique no. in a given array where all the elements are repeated twice with one value being unique.
#include<iostream>
#include<vector>
using namespace std;
int findUnique(vector<int> &v){
    for(int i=0; i<v.size(); i++){
        for(int j=i+1; j<v.size(); j++){
            if(v[i]==v[j]){
                v[i]=v[j]=-1;
            }
        }
    }
    for(int i=0; i<v.size(); i++)
        if(v[i]>0) return v[i];
        return -1;
}
int main(){
    vector<int> v={2,4,8,2,4};
    cout<<findUnique(v);
    return 0;
}
