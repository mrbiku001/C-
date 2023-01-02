// Q2. Find the sum of digits in given no. n.
//     Input: 12345
//     Output: 15
#include<iostream>
using namespace std;
int main(){
    int n,op,sum=0;
    cout<<"enter no.: ";
    cin>>n;

    op=n;
    while(op>0){
        sum+=op%10;
        op/=10;
    }
    cout<<"sum of all the digit of integer "<<n<<" = "<<sum;
    return 0;
}