// Q7. Converting Binary to Decimal
//     Input:8
//     Output:100
#include<iostream>
using namespace std;
int main(){
    int dec=0, binary,pw;
    cout<<"enter a Binary no: ";
    cin>>binary;

    pw=1;
    while(binary>0){
        dec+=pw*binary%10;
        pw*=2;
        binary/=10;
    }
    cout<<dec;
    return 0;
}