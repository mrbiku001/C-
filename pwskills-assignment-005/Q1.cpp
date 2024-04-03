// Q1 - Print the sum of the first 5 decimal numbers from 1 to 5 in binary format.(Easy)
//     Sample Input: 1,2,3,4,5
//     Sample Output: 1111
#include<iostream>
using namespace std;
int decimaltobinary(int dec){
    int pw=1,bin=0;
    while(dec>0){
        bin+=(dec%2)*pw;
        pw*=10;
        dec/=2;
    }
    return bin;
}
int main(){
    int in,sum=0,bin;
    for(int i=1; i<=5; i++){
        cout<<"enter decimal numbers: "<<i<<"th: ";
        cin>>in;
        sum+=in;
    }
    cout<<decimaltobinary(sum);
    return 0;
}