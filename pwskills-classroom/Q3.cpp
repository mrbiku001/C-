// Q3. Reverse the digit of a number.
//     Input: 12345
//     Output:54321
#include<iostream>
using namespace std;
int main(){
    int num,rev=0;
    cout<<"enter the no. n: ";
    cin>>num;

    while(num>0){
        rev=rev*10+num%10;
        num/=10;
    }
    cout<<"reverse = "<<rev;
    return 0;
}