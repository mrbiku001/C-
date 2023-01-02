// Q5. enter 2 number a and b and calculate a^b.
//     Input: 2 & 3
//     Output: 8
#include<iostream>
using namespace std;
int main(){
    int a,b,ans=1;
    cout<<"enter a & b: ";
    cin>>a>>b;
    for(int i=1; i<=b; i++){
        ans*=a;
    }
    cout<<ans;
    return 0;
}