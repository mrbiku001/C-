// Q6. Print pattern.
//     1234567
//     2345671
//     3456712
//     4567123
//     5671234
//     6712345
//     7123456
#include<iostream>
using namespace std;
int main(){
    int order;
    cout<<"enter order: ";
    cin>>order;
    for(int i=1; i<=order; i++){
        for(int j=1; j<=order-i+1; j++){
            cout<<j+i-1;
        }
        for(int j=1; j<=i-1; j++){
            cout<<j;
        }
        cout<<endl;
    }
}