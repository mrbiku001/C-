// Q21. Rotate the given array 'v' by k steps, where k is non-negative.
//using array concept.
/* #include<iostream>
using namespace std;
void rotate(int arr[], int k, int n){
    int rot[n], index=0;
    for(int i=n-k; i<n; i++){
        rot[index++]=arr[i];
    }
    for(int i=0; i<n-k; i++){
        rot[index++]=arr[i];
    }
    cout<<"[";
    for(int i=0; i<n; i++){
        cout<<rot[i];
        if(i!=n-1) cout<<",";
    }
    cout<<"]";
}
int main(){
    int arr[]={1,2,3,4,5,6,7,8,9};
    int k, n=sizeof(arr)/sizeof(arr[0]);
    cout<<"rotate by: ";
    cin>>k;
    k%=n;
    // while(k>n-1){
    //     k-=n;
    // }
    rotate(arr,k,n);
    return 0;
} */
//uisng vector cconcept
#include<bits/stdc++.h>
using namespace std;
int main(){
    vector<int> v={1,2,3,4,5,6,7};
    int k;
    cout<<"rotate by : ";
    cin>>k;
    k%=v.size();
    reverse(v.begin(), v.end());
    reverse(v.begin(), v.begin()+k);
    reverse(v.begin()+k, v.end());
    for(int i:v){
        cout<<i<<" ";
    }cout<<endl;
    return 0;
}