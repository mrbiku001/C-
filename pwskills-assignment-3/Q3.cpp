// Q3- Write a program to take input from user for Cost Price (C.P.) and Selling Price(S.P.) and calculate Profit or Loss. (Medium)
// 	Explanation :
// 	Formula for profit and loss
// 	Profit = S.P - C.P
// 	Loss = C.P - S.P
// 	(S.P is Selling Price and C.P is Cost Price)
// 	Sample Input :
// 	Enter cost price: 4000
// 	Enter selling price: 9560
// 	Sample Output :
// 	Profit = 5560
#include<iostream>
using namespace std;
int main(){
    int sp,cp;
    cout<<"enter S.P:";
    cin>>sp;
    cout<<"enter C.P:";
    cin>>cp;
    if(sp>cp){
        cout<<"you have profit of Rs. "<<sp-cp;
    }
    else if(cp>sp){
        cout<<"you have loss of Rs. "<<cp-sp;
    }
    else{
        cout<<"no profit no loss";
    }
    return 0;
}