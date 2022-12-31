// Q5 - Write a program to calculate the sum of digits of a 3 digit number. (Hard)
// 	Sample Input : 123
// 	Sample Output : 6
#include<iostream>
using namespace std;
int main(){
    int x,sum,dig;
    cout<<"enter 3 digit no:";
    cin>>x;
    for(int i=0; i<3; i++){
        dig=(x%10);
        sum+=dig;
        x/=10;
    }
    cout<<"sum = "<<sum;
    return 0;
}       