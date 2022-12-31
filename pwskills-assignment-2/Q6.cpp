// Q6 - Design a calculator to perform basic arithmetic operations (+,-,/,*,%) (Easy)
// 	Sample Input : 8 10
// 	Sample Output :
// 	Sum = 18
// 	Difference = -2
// 	Product = 80
// 	Division = 0.8
#include<iostream>
using namespace std;
int main(){
    float a,b;
    cout<<"enter a :";
    cin>>a;
    cout<<"enter b :";
    cin>>b;
    cout<<"Sum = "<<a+b<<endl;
    cout<<"Difference = "<<a-b<<endl;
    cout<<"Product = "<<a*b<<endl;
    cout<<"Division = "<<a/b<<endl;
    return 0;
}