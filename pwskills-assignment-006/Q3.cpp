// Q3 - Given the age of a person, write a function to check if the person is eligible to vote or not.(Easy)
//     Sample Input: 19
//     Sample Output: Yes
//     Sample Input: 17
//     Sample Output: No
#include<iostream>
using namespace std;
void eligibility(int age){
    (age>=18)?cout<<"Yes":cout<<"No";
}
int main(){
    int age;
    cout<<"enter your age: ";
    cin>>age;
    eligibility(age);
    return 0;
}