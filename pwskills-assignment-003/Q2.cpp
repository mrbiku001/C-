// Q2 - Write a program to print absolute value of a number entered by the user. (Easy)
// 	Sample Input: -1
// 	Sample Output: 1
#include<iostream>
using namespace std;
int main(){
    int x;
    cout<<"enter a num:";
    cin>>x;
    (x>0)?cout<<x:cout<<-1*x;
    return 0;
}