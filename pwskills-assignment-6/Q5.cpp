// Q5 - Given two numbers a and b, write a program to print all the prime numbers present between a and b.(Hard)
//     Sample Input: 2 10
//     Sample Output: 2 3 5 7
#include<iostream>
using namespace std;
void primebetn(int a, int b){
    int j;
    for(int i=a; i<=b; i++){
        for(j=2; j<i; j++){
            if(i%j==0){
                break;
            }
        }
        if(j==i){
                cout<<i<<" ";
            }
    }
}
int main(){
    int a, b;
    cout<<"enter range: ";
    cin>>a>>b;
    primebetn(a,b);
    return 0;
}