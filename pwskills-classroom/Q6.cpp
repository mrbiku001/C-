// Q6. Print nth factorial no.
//     Input: 3
//     Output: 3!=6
#include<iostream>
using namespace std;
int main(){
    int num,fact=1;
    cout<<"enter number: ";
    cin>>num;
    for(int i=1; i<=num; i++){
        fact*=i;
    }
    cout<<"factorial = "<<fact;
}