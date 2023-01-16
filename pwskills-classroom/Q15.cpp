// Q15. Check if the give array is shorted or not.
#include<iostream>
#include<vector>
using namespace std;
bool check(vector<int> &v){
    int ans=true;
    for(int i=1; i<v.size(); i++){
        if(v[i]<v[i-1]){
            ans=false;
            break;
        }
    }
    return ans;
}
int main(){
    vector<int> v={1,2,3,4,5};
    cout<<check(v);
    return 0;
}