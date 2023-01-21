// Q22. Foe Q inputs, check of the given no. is present in the array or not.
// Note:-value of all the array is less than 10^5
#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0; i<n; i++){
        cin>>a[i];
    }

    const int N = 1e5+10;
    //creating a frequancy array as max(a[i])<10^5
    vector<int> freq(N,0);
    for(int i=0; i<n; i++){
        freq[a[i]]++;
    }

    int q;
    cin>>q;
    while(q--){
        int val;
        cin>>val;
        if(freq[val]>0){
            cout<<"YES"<<endl;
        }else cout<<"NO"<<endl;
    }
    return 0;
}