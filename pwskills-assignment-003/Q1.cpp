// Q1 - Write a program which takes the values of length and breadth from user and check if it is a square or not. (Easy)
// 	Sample Input :
// 	Enter length: 5
// 	Enter breadth: 4
// 	Sample Output : It is a rectangle.
#include<iostream>
using namespace std;
int main(){
    int length,breadth;
    cout<<"enter length:";
    cin>>length;
    cout<<"enter breadth:";
    cin>>breadth;
    (length==breadth)?cout<<"it is a square":cout<<"it is a rectangle";
    return 0;
}