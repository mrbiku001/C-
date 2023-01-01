// Q1 - Write a program to calculate the factorial of a number.
// 	Explanation : Factorial of any number n is represented by n! and is equal to 1*2*3*....*(n-1)*n.
// 	E.g.-
// 	4! = 1*2*3*4 = 24
// 	3! = 3*2*1 = 6
// 	Also,
// 	1! = 1
// 	0! = 0
#include<iostream>
using namespace std;
int main(){
    int x,f=1;
    cout<<"enter a number:";
    cin>>x;
    if(x==0){
        cout<<"factorial = "<<1;
        return 0;
    }
    else{
        while(x>0){
        f*=x;
        x--;
    }
    }
    cout<<"factorial = "<<f;
    return 0;
}