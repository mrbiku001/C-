// Q1. Count the number of digit in given number n.
//     Input: 12345
//     Output:5
#include<iostream>
using namespace std;
int main(){
    int n,op, count=0;
    cout<<"enter a number: ";
    cin>>n;

    op=n;
    while(op>0){
        op/=10;
        count++;
    }
    cout<<"no. of digit in "<<n<<" = "<<count;
    return 0;
}