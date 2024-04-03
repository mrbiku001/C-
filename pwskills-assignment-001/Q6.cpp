// Q6 - Write a C++ program to swap two numbers with the help of a third variable. (Hard)
#include<iostream>
using namespace std;
int main(){
    int x,y;
    cout<<"enter value of x:";
    cin>>x;
    cout<<"enter value of y:";
    cin>>y;
    int temp=x;
    x=y;
    y=temp;
    cout<<"x = "<<x<<endl;
    cout<<"y = "<<y<<endl;
    return 0;
}