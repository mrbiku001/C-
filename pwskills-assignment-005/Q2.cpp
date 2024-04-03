// Q2 - Given a natural number, find the number of 0’s in the binary representation of that number.(Medium)
//     Note: Don’t count the preceding zeros.
//     For example: 001001 has 2 zeros as the first two zeros from left are preceding zeros.

//     Sample Input:9
//     Sample Output: 2
//     Explanation: As the binary representation of 9 is 1001
//     Sample Input: 6
//     Sample Output: 1
//     Explanation: As the binary representation of 6 is 0110
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
int zerosinbin(int bin){
    int ans,count=0;
    while(bin>0){
        if(bin%10==0){
            count++;
        }
        bin/=10;
    }
    return count;
}
int main(){
    int dec,ans;
    cout<<"enter decimal no.: ";
    cin>>dec;
    ans=zerosinbin(decimaltobinary(dec));
    cout<<"no. of 0's: "<<ans;
    return 0;
}