// Q4-1. print pattern.
//        *
//       **
//      ***
//     ****
#include<iostream>
using namespace std;
int main(){
    int order,d;

    cout<<"enter order:";
    cin>>order;
    for(int i=1; i<=order; i++){
        for(int j=1; j<=order-i; j++){
            cout<<" ";
        }
        for(int j=1;j<=i; j++){
            cout<<"*";
        }
        cout<<endl;
    }
    return 0;
}