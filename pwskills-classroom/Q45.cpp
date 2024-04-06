// Q45. Given Two no. x & y Find the greatest common divisior of x & y using recursion.
//     Inp1: x=4, y=9      Out1: 1
//     Inp2: x=12, y=20    Out2: 4
#include <iostream>
using namespace std;
int gcd(int a, int b){
    if(b>a) return gcd(b,a);
    if(b==0) return a;
    return gcd(b, a%b);
}
int main(){
    int a,b;
    cout<<"Enter Input: ";
    cin>>a>>b;

    cout<<gcd(a,b);
    return 0;
}