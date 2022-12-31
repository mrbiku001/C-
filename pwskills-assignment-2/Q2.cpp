// Q2 - Write a program to take the values of two variables a and b from the keyboard and then check ifboth the conditions 'a < 50' and 'a < b' are true. (Easy)
#include<iostream>
using namespace std;
int main(){
    int a,b;
    cout<<"enter a: ";
    cin>>a;
    cout<<"enter b: ";
    cin>>b;
    cout<<(a<50)&&(a<b);
}