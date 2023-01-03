// Q8. Converting Decimal to Binary.
//     Input:4
//     Output:100
#include<iostream>
using namespace std;
int main(){
    int bin=0,dec,pw=1;
    cout<<"enter decimal no.: ";
    cin>>dec;
    while(dec>0){
        bin=bin+(dec%2)*pw;
        pw*=10;
        dec=dec/2;
    }
    cout<<"your binary no. "<<bin;
    return 0;
}