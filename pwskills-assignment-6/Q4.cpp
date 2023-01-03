// Q4 - Given two numbers a and b, write a program using functions to print all the odd numbers between them.(Medium)
//     Sample Input: 1 10
//     Sample Output: 1 3 5 7 9
#include<iostream>
using namespace std;
void oddnobetween(int a, int b){
    for(int i=a; i<=b; i++){
        if(i%2==1) cout<<i<<" ";
    }
}
int main(){
    int a, b;
    cout<<"enter no's a & b: ";
    cin>>a>>b;
    oddnobetween(a,b);
    return 0;
}