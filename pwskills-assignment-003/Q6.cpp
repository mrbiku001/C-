// Q6. Write a program to calculate marks to grades . Follow the conversion rule as given below :(Medium)
// 	100 – 90 A+
// 	90 – 80 A
// 	80 – 70 B+
// 	70 – 60 B
// 	60 – 50 C
// 	50 – 40 D
// 	40 – 30 E
// 	30 – 0 F

// 	Sample Input : Enter Your Marks: 98
// 	Sample Output : Your Grade is A+
#include<iostream>
using namespace std;
int main(){
    int marks;
    cout<<"enter marks:";
    cin>>marks;
    if((marks>=90)&&(marks<100)){
        cout<<"Your grade is A+";
    }
    else if((marks>=80)&&(marks<90)){
        cout<<"Your grade is A";
    }
    else if((marks>=70)&&(marks<80)){
        cout<<"Your grade is B+";
    }
    else if((marks>=60)&&(marks<70)){
        cout<<"Your grade is B";
    }
    else if((marks>=50)&&(marks<60)){
        cout<<"Your grade is C";
    }
    else if((marks>=40)&&(marks<50)){
        cout<<"Your grade is D";
    }
    else if((marks>=30)&&(marks<40)){
        cout<<"Your grade is E";
    }
    else if((marks>=0)&&(marks<30)){
        cout<<"Your grade is F";
    }
    else{
        cout<<"enter valid number";
    }
    return 0;
}