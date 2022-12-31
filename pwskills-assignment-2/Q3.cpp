// Q3 - There are 45 total pupils in the class, 25 of whom are boys. Write a program to find how manygirls received grades "A" if 17 boys made up 80% of the students that received grades "A". (Medium)
#include<iostream>
using namespace std;
int main(){
    int total,boys=17,girls;
    total = 80*45/100;
    girls=total-boys;
    cout<<girls;
    return 0;
}