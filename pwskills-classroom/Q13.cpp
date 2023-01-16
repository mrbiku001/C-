// Q13. Count the number of occurrences of a particular element x.
#include<iostream>
#include<vector>
using namespace std;
int occurance(vector<int> &v, int x){
    int count=0;
    for(int i:v){
        if(i==x) count++;
    }
    return count;
}
int main(){
    vector<int> v={5,2,6,7,8,9,4,2,3,5};
    int x;
    cout<<"enter integer : ";
    cin>>x;
    cout<<"no. of occurance of "<<x<<" in vector v is = "<<occurance(v,x); 
    return 0;
}