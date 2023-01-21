// Q28. Given an array of integer 'a', of size n. For q number of inputs, print the sum of values in a given range of indices from l(starting index for the range) to r(ending index for the range), both l and r included in the sum.
//     more formally, print a[l]+a[l+1]+a[l+2]+.....+a[r] for each q.
//     Note: Array 'a' follows 1-based indexing i.e. element 1 is at index 1 and not 0, as usually is.
    // Input: 5 //no. of element in array.
    //     5 1 2 3 4 //all the elements (space seprated)
    //     4 //value of Q
    //     1 1 //l and r for the 1st q, q=1
    //     1 3 //l and r for the 2st q, q=2
    //     4 5 //l and r for the 3st q, q=3
    //     1 5 //l and r for the 4st q, q=4
    // Output: 
    // 5 //sum from a[1] to a[1] i.e. 5 itself
    // 8 //sum from a[1] to a[3] i.e. 5+1+2=8
    // 7 //sum from a[4] to a[5] i.e. 4+3=7
    // 15 //sum from a[1] to a[5] i.e. 5+1+2+3+4=15
#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n;
    cin>>n;

    vector<int> v(n+1,0); //initiating vector of size n+1 and declearnig all the element to be 0
    for(int i=1; i<=n; i++){
        //as given 1-based indexing
        cin>>v[i];
    }
    //calculate prefix sum array
    for(int i=1; i<=n; i++){
        v[i]+=v[i-1];
    }

    int q;
    cin>>q;
     
     while(q--){
        int l,r;
        cin>>l>>r;

        int ans=0;
        //ans=prefixsumarray[r]-prefixsumarray[l-1]
        ans=v[r]-v[l-1];
        cout<<ans<<endl; 
     }
    return 0;
}
//0 5 1 2 3 4
//0 5 6 8 11 15-->>prefix sum array
//l=1,r=3
//ans=v[r]-v[l-1]=v[3]-v[0]=8-0=8

//l=2, r=5
//ans=v[r]-v[l-1]=v[5]-v[i]=15-5=10