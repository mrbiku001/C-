// Q5- Create a calculator using switch statement to perform addition, subtraction, multiplication and division.
// 	Sample Input :
// 	Enter an operator (+, -, *, /): -
// 	Enter two numbers:
// 	6
// 	8
// 	Sample Output : 6 - 8 = -2
#include<iostream>
using namespace std;
int main(){
    float a,b;
    char op;
    cout<<"enter a:";
    cin>>a;
    cout<<"enter b:";
    cin>>b;
    cout<<"enter an operator for operation (+,-,*,/) ";
    cin>>op;
    switch (op)
    {
    case '+':
        cout<<"sum = "<<a+b;
        break;
    case '-':
        cout<<"difference = "<<a-b;
        break;
    case '*':
        cout<<"product = "<<a*b;
        break;
    case '/':
        cout<<"division = "<<a/b;
        break;
    default:
        cout<<"kindly enter a valid operator";
    }
    return 0;
}