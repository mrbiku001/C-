// Q1 - Write a function to print squares of the first 5 natural numbers.(Easy)
//     Sample Output: 1 4 9 16 25
#include<iostream>
using namespace std;
void sqfirstfive(){
    for(int i=1; i<=5; i++){
        cout<<i*i<<" ";
    }
}
int main(){
    sqfirstfive();
    return 0;
}