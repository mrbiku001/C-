// Q3 - Given two binary numbers, return the greatest of these numbers in decimal format.(Easy)
//     Sample Input: 1001 and 0100
//     Sample Output: 9
#include<iostream>
using namespace std;
int binarytodecimal(int bin){
    int dec=0,pw=1;
    while(bin>0){
        dec+=(bin%10)*pw;
        pw*=2;
        bin/=10;
    }
    return dec;
}
int main(){
    int bin1,bin2;
    cout<<"enter 2 binary no.: ";
    cin>>bin1>>bin2;
    (bin1>bin2)?cout<<binarytodecimal(bin1):cout<<binarytodecimal(bin2);
    return 0;
}