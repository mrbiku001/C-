// Q4- Write a program to print positive number entered by the user, if user enters a negative number, it is skipped.(Medium)
// 	Sample Input : Enter an integer: -6
// 	Sample Output : The number is negative and skipped
#include<iostream>
using namespace std;
int main(){
    int x;
    cout<<"enter a number";
    cin>>x;
    (x>0)?cout<<x:cout<<"The number is negative and skipped";
    return 0;
}