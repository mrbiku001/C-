// Q4 - Write a program to calculate the sum of the first and the second last digit of a 5 digit number. (Hard)
// 	Sample Input : 12345
// 	Sample Output : 1+4=5
#include<iostream>
using namespace std;
int main(){
    int x;
    cout<<"enter 5 digit no.";
    cin>>x;
    int f=x/10000;
    int l=x%10;
    cout<<f+l;
    return 0;
}