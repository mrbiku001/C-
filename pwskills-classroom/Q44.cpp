// Q44. Given a no. n. Find the sum of natural no. till n but with alternate signs.
//     That mesns if n=5 then 1-2+3-4+5 = 3
//     Int n=10 Out -5
//     Int n=5 Out 3
#include <iostream>
using namespace std;
int rF(int n){
    if(n == 0) return 0;

    return rF(n-1) + ((n%2)?(n):(-n));
}
int main(){
    int n;
    cout<<"Enter n: ";
    cin>>n;

    cout<<rF(n);
    return 0;
}