// Q3 - Write a program to find the sum of n natural numbers.
// 	Sample Input : 5
// 	Sample Output : 15
#include<iostream>
using namespace std;
int main(){
    int x=0,num,sum=0;
    cout<<"enter a number:";
    cin>>num;
    x=num;
    while(x>0){
        sum+=x;
        x--;
    }
    cout<<"sum of "<<num<<" natural number is "<<sum;
    return 0;
}