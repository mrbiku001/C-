// Q4 - Write a program to reverse a given integer number.
// 	Sample Input : 538
// 	Sample Output : 835
#include<iostream>
using namespace std;
int main(){
    int r=0,t,num;
    cout<<"enter a integer: ";
    cin>>num;
    t=num;
    while (num>0){
        r=(num%10)+r*10;
        num/=10;
    }
    cout<<"reverse integer "<<t<<" = "<<r;
    return 0;
}