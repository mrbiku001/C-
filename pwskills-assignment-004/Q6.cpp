// Q6- Write a program to print alphabet diamond pattern:
// A
// ABC
// ABCDE
// ABCDEFG
// ABCDEFGHI
// ABCDEFG
// ABCDE
// ABC
// A
#include<iostream>
using namespace std;
int main(){
    int order;
    char c='A';
    cout<<"enter order(a odd no.): ";
    cin>>order;
    for(int i=1; i<=(order+1)/2; i++){
        for(int j=1; j<=(order+1)/2; j++){
            if(j==1){
                cout<<c++;
            }
            else{
                if(j<=i){
                    cout<<c++<<c++;
                }
            }
        }
        cout<<endl;
        c='A';
    }
    for(int i=(order-1)/2; i>=1; i--){
        for(int j=(order-1)/2; j>=1; j--){
            if(j==(order-1)/2){
                cout<<c++;
            }
            else{
                if(j<i){
                    cout<<c++<<c++;
                }
            }
        }
        cout<<endl;
        c='A';
    }
    return 0;
}