// Q43. Given a number num and a value k. print k multiples of num.
//     k>0
//     Int: num=12, k=5
//     Out: 12, 24, 36, 48, 60
    
//     Int: num = 3, k=8
//     Out: 3,6,9,12,15,18,21,24
#include <iostream>
using namespace std;
void rF(int num, int k){
    if(k == 0){
        return;
    }
    rF(num, k-1);
    cout<<num*(k)<<" ";
}
int main(){
    int num, k;
    cout<<"Enter num & k: ";
    cin>>num>>k;
    rF(num,k);
    return 0;
}