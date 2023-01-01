// Q2 - Write a program to print all Armstrong numbers between 100 to 500.
// 	Explanation : A three digit number is called the Armstrong number if the sum of the cube of its digit is equal to
// 	the number itself.
// 	E.g.- 153 is an Armstrong number because (13)+(53)+(33) = 153.
// 	Sample Input : Already mentioned (100 to 500)
#include<iostream>
using namespace std;
int main(){
    cout<<"all Armstrong numbers between 100 to 500."<<endl;
    for(int i=100; i<500; i++){
        int sum=0,t=i;
        while(t!=0){
            sum=sum+(t%10)*(t%10)*(t%10);
            t=t/10;
        }
        if (sum==i){
            cout<<i<<endl;
        }
    }
    return 0;
}